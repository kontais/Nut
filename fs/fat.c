#include <fat.h>
#include <pio.h>
/**
 * 
 * fat_index : 0,2,3...
 * 
 */
static void compute_fat_for_cluster(fatfs *fs, uint8_t fat_index, uint32_t cluster, uint32_t *sec_off, uint32_t *entry_off)
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
	*fatsec_off = fs->BPB->BPB_ResvdSecCnt + (FATOffset / fs->BPB->BPB_BytsPerSec) + (fat_index * fs->FATsecs);
	*entry_off = FATOffset % fs->BPB->BPB_BytsPerSec;
}

static void uint32_t extract_fat_entry(fatfs *fs, uint32_t cluster)
{
	uint8_t buf[512];
	uint32_t sec_off, entry_off;
	uint32_t entry;
	compute_fat_for_cluster(fs, 0, &sec_off, &entry_off);
	pio_read_sector(buf, sec_off);
	switch(fs->Type)
	{
		case FAT12:
			entry = *(uint16_t *)&buf[entry_off];
			if (cluster & 0x0001)
				entry >> = 4;
			else
				entry & = 0x0fff;
			break;
		case FAT16:
			entry = *(uint16_t *)buf[entry_off];
			break;
		case FAT32:
			entry = *(uint32_t *)buf[entry_off] & 0x0FFFFFFF;
			break;
		default:
			bug("Invalid FAT type!\n");
			break;
	}
	return entry;
}


void fatfs_init(fatfs *fs)
{
	pio_read_sector(&fs->BPB, 2048);
	
	fs->RootDirSec = ((fs->BPB->BPB_RootEntCnt * 32) + (fs->BPB->BPB_BytsPerSec - 1)) / fs->BPB->BPB_BytsPerSec;
	fs->FATSec = fs->BPB->BPB_FATSz16 != 0 ? fs->BPB->BPB_FATSz16 : fs->BPB->BPB_FATSz32;
	fs->TotSec = fs->BPB->BPB_TotSec16 != 0 ? fs->BPB->BPB_TotSec16 : fs->BPB->BPB_TotSec32;
	fs->DataSec = fs->TotSec - (fs->BPB->BPB-ResvdSecCnt + (fs->BPB->BPB_NumFATs * fs->FATSec) + fs->RootDirSec);
	fs->CountOfClus = fs->DataSec / fs->BPB->BPB_SecPerClus;
	if (fs->CountOfClus < 4085)
		fs->Type = FAT12;
	else if (fs->CountOfClus < 65525)
		fs->Type = FAT16;
	else
		fs->Type = FAT32;
}

//Max is the number of entries.
int read_lname(struct LongNameDirEntry *dir_entry, char *lname, uint32_t max)
{
	struct LongNameDirEntry *entry = dir_entry;
	
	while(entry->LDIR_Type == ATTR_LONG_NAME)
	{
		entry ++;
		
		if (entry > max + dir_entry)
			return -1;
	}
	
	entry --;
	
	if (entry->LDIR_Type != ATTR_LONG_NAME)
		return -1;
	
	do
	{
		if (entry->LDIR_Name1[0] == 0xffff)
			break;
		lname = wstrncpy(lname, entry->LDIR_Name1, 5);
		if (entry->LDIR_Name2[0] == 0xffff)
			break;
		lname = wstrncpy(lname, entry->LDIR_Name2, 6);
		if (entry->LDIR_Name3[0] == 0xffff)
			break;
		lname = wstrncpy(lname, entry->LDIR_Name3, 2);
		
		if (entry < dir_entry)
			return -1;
	} while(!((entry--)->LDIR_Ord & 0x40));
	
	return 0;
}
