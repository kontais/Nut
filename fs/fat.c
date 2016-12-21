#include <fat.h>
#include <isa.h>
/**
 * 
 * fat_index : 0,2,3...
 * 
 */
void compute_fat_for_cluster(FATFS_Type *fs, uint8_t fat_index, uint32_t cluster, uint32_t *sec_off, uint32_t *entry_off)
{
	uint32_t FATOffset;
	switch(fs->Type)
	{
		case FAT12:
			FATOffset = cluster + cluster / 2;
			break;
		case FAT16:
			FATOffset = cluster * 2;
			break;
		case FAT32:
			FATOffset = cluster * 4;
			break;
		default:
			bug("Invalid FAT type!\n");
			break;
	}
	*sec_off = fs->FirstFATSec + (FATOffset / fs->BPB->BPB_BytsPerSec) + (fat_index * fs->FATSecs);
	*entry_off = FATOffset % fs->BPB->BPB_BytsPerSec;
}

uint32_t extract_fat_entry(FATFS_Type *fs, uint32_t cluster)
{
	uint8_t buf[512];
	uint32_t sec_off, entry_off;
	uint32_t entry;
	compute_fat_for_cluster(fs, 0, cluster, &sec_off, &entry_off);
	pio_read_sector(buf, sec_off + fs->LBAStart);
	switch(fs->Type)
	{
		case FAT12:
			entry = *(uint16_t *)(buf + entry_off);
			if (cluster & 0x0001)
				entry >>= 4;
			else
				entry &= 0x0fff;
			break;
		case FAT16:
			entry = *(uint16_t *)(buf + entry_off);
			break;
		case FAT32:
			entry = *(uint32_t *)(buf + entry_off) & 0x0FFFFFFF;
			break;
		default:
			bug("Invalid FAT type!\n");
			break;
	}
	return entry;
}
void read_cluster(FATFS_Type *fs, void *buf, uint32_t cluster)
{
	uint32_t count = fs->BPB->BPB_SecPerClus;
	uint32_t start = fs->LBAStart + fs->FirstDataSec + (cluster - 2) * fs->BPB->BPB_SecPerClus;
	for (int i = 0; i  < count; i ++)
	{
		pio_read_sector(buf + (i << 9), start + i);
	}
}
uint32_t compute_cluster_chain_length(FATFS_Type *fs, uint32_t cluster)
{
	uint8_t end = 0;
	uint32_t chain_length = 0;
	do 
	{
		chain_length ++;
		cluster = extract_fat_entry(fs, cluster);
		switch(fs->Type)
		{
			case FAT12:
				if (cluster == FAT12_ENTRY_END_OF_FILE)
					end = 1;
				break;
			case FAT16:
				if (cluster == FAT16_ENTRY_END_OF_FILE)
					end = 1;
				break;
			case FAT32:
				if (cluster == FAT32_ENTRY_END_OF_FILE)
					end = 1;
				break;
			default:
				bug("Invalid FAT type!\n");
				break;
		}
	} while(!end);
	return chain_length;
}
uint32_t read_cluster_chain(FATFS_Type *fs, void *buf, uint32_t bufsize, uint32_t cluster, uint32_t cluster_offset)
{
	uint8_t end = 0;
	uint32_t read_size = 0;
	do 
	{
		//Avoid overflow
		if (bufsize < read_size + fs->BPB->BPB_SecPerClus * 512)
			break;
		
		if (cluster_offset == 0)
		{
			read_cluster(fs, buf + read_size, cluster);
			read_size += fs->BPB->BPB_SecPerClus * 512;
		}
		else
			cluster_offset --;
		
		cluster = extract_fat_entry(fs, cluster);
		
		switch(fs->Type)
		{
			case FAT12:
				if (cluster == FAT12_ENTRY_END_OF_FILE)
					end = 1;
				break;
			case FAT16:
				if (cluster == FAT16_ENTRY_END_OF_FILE)
					end = 1;
				break;
			case FAT32:
				if (cluster == FAT32_ENTRY_END_OF_FILE)
					end = 1;
				break;
			default:
				bug("Invalid FAT type!\n");
				break;
		}
		
	} while(!end);
	
	return read_size;
}


//Max is the number of entries.
int read_lname(LongNameDirEntry_Type *dir_entry, char *lname, uint32_t max)
{
	int offset;
	char buf[512];
	wchar *unicode_lname = (wchar *)buf;
	struct LongNameDirEntry *entry = dir_entry;
	while(entry->LDIR_Attr == ATTR_LONG_NAME)
	{
		entry ++;
		
		if (entry > max + dir_entry)
			return -1;
	}
	
	offset = entry - dir_entry;
	entry --;
	
	if (entry->LDIR_Attr != ATTR_LONG_NAME)
		return -1;
	
	do
	{
		if (entry->LDIR_Name1[0] == 0xffff)
			break;
		unicode_lname = wstrncpy(unicode_lname, entry->LDIR_Name1, 5);
		if (entry->LDIR_Name2[0] == 0xffff)
			break;
		unicode_lname = wstrncpy(unicode_lname, entry->LDIR_Name2, 6);
		if (entry->LDIR_Name3[0] == 0xffff)
			break;
		unicode_lname = wstrncpy(unicode_lname, entry->LDIR_Name3, 2);
		
		if (entry < dir_entry)
			return -1;
	} while(!((entry--)->LDIR_Ord & 0x40));
	loop_unicode_into_utf8(buf, lname);
	
	return offset;
}

uint32_t read_file(FATFS_Type *fs, const char *name, void *buf, uint64_t bufsize)
{
	uint32_t rootdir_size = compute_cluster_chain_length(fs, fs->BPB->ExtBPB.Ext_BPB_32.BPB_RootClus) * fs->BPB->BPB_SecPerClus << 9;
	void *rootdir = malloc(rootdir_size);
	assert(rootdir != NULL);
	if (read_cluster_chain(fs, rootdir, rootdir_size, fs->BPB->ExtBPB.Ext_BPB_32.BPB_RootClus, 0) != rootdir_size)
		bug("Reading root directory failed unexpectedly");
	
	char name_buf[512] = {0};
	uint32_t pos = 0;
	int ret;
	do
	{

		if ((ret = read_lname((LongNameDirEntry_Type *)rootdir + pos, name_buf, (rootdir_size >> 5) - pos)) == -1)
		{
			bug("Extracting file name from root directory failed unexpectedly");
			break;
		}
		pos += ret + 1;
	} while(strcmp(name_buf, name) != 0);
	
	Dir_Struc_Type *dir_struct = (Dir_Struc_Type *)rootdir + pos - 1;
	
	if (bufsize < dir_struct->DIR_FileSize)
		return 0;
	
	return read_cluster_chain(fs, buf, bufsize, dir_struct->DIR_FstClusHI << 16 | dir_struct->DIR_FstClusLO, 0);
}

void fatfs_init(FATFS_Type *fs)
{
	fs->LBAStart = 2048;
	fs->BPB = malloc(sizeof(BPB_Type));
	assert(fs->BPB != NULL);
	
	//The partition begins at 2048 sectors.
	pio_read_sector(fs->BPB, fs->LBAStart);
	
	fs->RootDirSecs = ((fs->BPB->BPB_RootEntCnt * 32) + (fs->BPB->BPB_BytsPerSec - 1)) / fs->BPB->BPB_BytsPerSec;
	fs->FATSecs = fs->BPB->BPB_FATSz16 != 0 ? fs->BPB->BPB_FATSz16 : fs->BPB->ExtBPB.Ext_BPB_32.BPB_FATSz32;
	fs->TotSecs = fs->BPB->BPB_TotSec16 != 0 ? fs->BPB->BPB_TotSec16 : fs->BPB->BPB_TotSec32;
	fs->DataSecs = fs->TotSecs - (fs->BPB->BPB_RsvdSecCnt + (fs->BPB->BPB_NumFATs * fs->FATSecs) + fs->RootDirSecs);
	fs->CountOfClus = fs->DataSecs / fs->BPB->BPB_SecPerClus;
	
	fs->FirstFATSec = fs->BPB->BPB_RsvdSecCnt;
	fs->FirstDataSec = fs->BPB->BPB_RsvdSecCnt + (fs->BPB->BPB_NumFATs * fs->FATSecs + fs->RootDirSecs);
	if (fs->CountOfClus < 4085)
	{
		fs->Type = FAT12;
		fs->FirstRootSec = fs->BPB->BPB_RsvdSecCnt + fs->BPB->BPB_NumFATs * fs->BPB->BPB_FATSz16;
	}
	else if (fs->CountOfClus < 65525)
	{
		fs->Type = FAT16;
		fs->FirstRootSec = fs->BPB->BPB_RsvdSecCnt + fs->BPB->BPB_NumFATs * fs->BPB->BPB_FATSz16;
	}
	else
	{
		fs->Type = FAT32;
		fs->FirstRootSec = fs->FirstDataSec + fs->BPB->ExtBPB.Ext_BPB_32.BPB_RootClus * fs->BPB->BPB_SecPerClus;
	}
}

// FATDir_Type *fatfs_opendir(FATFS_Type *fs, const char *path)
// {
// 	
// 	FATDir_Type *fatdir = malloc(sizeof(FATDir_Type));
// 	fatdir->buf = 
// 	
// }
// FATFile_Type fatfs_readdir(FATFS_Type *fs, FATDir_Type *dir)
// {
// 	
// }
// void fatfs_rewinddir(FATFS_Type *fs, FATDir_Type *dir)
// {
// 	
// }
// void fatfs_closedir(FATFS_Type *fs, FATDir_Type *dir)
// {
// 	
// }
// 
// void fatfs_readfile(FATFS_Type *fs, FATFile_Type *file)
// {
// }
