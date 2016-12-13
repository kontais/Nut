#ifndef _FAT_H_
#define _FAT_H_

//BPB structure common to FAT12, FAT16 and FAT32 implementations
typedef struct BPB
{
	uint8_t BS_jmpBoot[3];
	uint8_t BS_OEMName[8];
	uint8_t BPB_BytsPerSec[2];
	uint8_t BPB_SecPerClus;
	uint8_t BPB_RsvdSecCnt[2];
	uint8_t BPB_NumFATs;
	uint8_t BPB_RootEntCnt[2];
	uint8_t BPB_TotSec16[2];
	uint8_t BPB_Media;
	uint8_t BPB_FATSz16[2];
	uint8_t BPB_SecPerTrk[2];
	uint8_t BPB_NumHeads[2];
	uint8_t BPB_HiddSec[4];
	uint8_t BPB_TotSec32[4];
}BPB;

typedef struct Ext_PBP
{
	uint8_t BS_DrvNum;
	uint8_t BS_Reserved1;
	uint8_t BS_BootSig;
	uint8_t BS_VolID[4];
	uint8_t BS_VolLab[11];
	uint8_t BS_FilSysType[8];
	uint8_t _reserved_1[420]; //Set to 0x00
	uint8_t Signature_word[2]; //0x55(at 510) 0xAA(at 511)
}Ext_PBP;

typedef enum FAT_TYPE
{
	FAT12,
	FAT16,
	FAt32
}FAT_TYPE;

typedef struct FSInfo
{
	uint8_t FSI_LeadSig[4];
	uint8_t FSI_Reserved1[480];
	uint8_t FSI_StrucSig[4];
	uint8_t FSI_Free_Count[4];
	uint8_t FSI_Nxt_Free[4];
	uint8_t FSI_Reserved2[12];
	uint8_t FSI_TrailSig[4];
}FSInfo;

typedef struct Dir_Struc
{
	uint8_t DIR_Name[11];
	uint8_t DIR_Attr;
	uint8_t DIR_NTRes;
	uint8_t DIR_CtrTimeTenth;
	uint8_t DIR_CtrTIme[2];
	uint8_t DIR_CtrDate[2];
	uint8_t DIR_LstAccDate[2];
	uint8_t DIR_FstClusHI[2];
	uint8_t DIR_WriTime[2];
	uint8_t DIR_WritDate[2];
	uint8_t DIR_FstClusLO[2];
	uint8_t DIR_FileSize[4];
}Dir_Struc;

#define ATTR_READ_ONLY	0x01
#define ATTR_HIDDEN	0x02
#define ATTR_SYSTEM	0x04
#define ATTR_VOLUMN_ID	0x08
#define ATTR_DIRECTORY	0x10
#define ATTR_ARCHIVE	0x20

typedef struct LongNameDirEntry
{
	uint8_t LDIR_Ord;
	uint8_t LDIR_Name1[10];
	uint8_t LDIR_Attr;
	uint8_t LDIR_Type;
	uint8_t LDIR_Chksum;
	uint8_t LDIR_Name2[12];
	uint8_t FstClusLO[2];
	uint8_t LDIR_Name3[4];
}LongNameDirEntry;


FAT_TYPE extract_fat_type();
uint32_t get_fat_entry(uint32_t cluster);


#endif
