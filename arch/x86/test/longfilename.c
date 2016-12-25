#include<klibc.h>

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












