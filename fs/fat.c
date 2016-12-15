#include <fat.h>
#include <isa.h>
/**
 * 
 * fat_index : 0,2,3...
 * 
 */
void compute_fat_for_cluster(fatfs *fs, uint8_t fat_index, uint32_t cluster, uint32_t *sec_off, uint32_t *entry_off)
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

uint32_t extract_fat_entry(fatfs *fs, uint32_t cluster)
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
void read_cluster(fatfs *fs, void *buf, uint32_t cluster)
{
	uint32_t count = fs->BPB->BPB_SecPerClus;
	uint32_t start = fs->LBAStart + fs->FirstDataSec + (cluster - 2) * fs->BPB->BPB_SecPerClus;
	for (int i = 0; i  < count; i ++)
	{
		pio_read_sector(buf + (i << 9), start + i);
	}
}
uint32_t read_file(fatfs *fs, void *buf, uint32_t bufsize, uint32_t cluster)
{
	uint8_t end = 0;
	uint32_t read_size = 0;
	do 
	{
		read_cluster(fs, buf + read_size, cluster);
		cluster = extract_fat_entry(fs, cluster);
		read_size += fs->BPB->BPB_SecPerClus * 512;
		
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
}

void fatfs_init(fatfs *fs)
{
	fs->LBAStart = 2048;
	fs->BPB = malloc(sizeof(BPB_Type));
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

