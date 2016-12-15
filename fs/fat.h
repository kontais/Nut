#ifndef _FAT_H_
#define _FAT_H_

//BPB structure common to FAT12, FAT16 and FAT32 implementations
typedef struct BPB __attribute__((packed))
{
	uint8_t BS_jmpBoot[3];
	uint8_t BS_OEMName[8];
	uint16_t BPB_BytsPerSec;
	uint8_t BPB_SecPerClus;
	uint16_t BPB_RsvdSecCnt;
	uint8_t BPB_NumFATs;
	uint16_t BPB_RootEntCnt;
	uint16_t BPB_TotSec16;
	uint8_t BPB_Media;
	uint16_t BPB_FATSz16;
	uint16_t BPB_SecPerTrk;
	uint16_t BPB_NumHeads;
	uint32_t BPB_HiddSec;
	uint32_t BPB_TotSec32;
}BPB_Type;

typedef struct Ext_PBP_12_16  __attribute__((packed))
{
	uint8_t BS_DrvNum;
	uint8_t BS_Reserved1; //Set value to 0x0
	uint8_t BS_BootSig;
	uint32_t BS_VolID;
	uint8_t BS_VolLab[11];
	uint8_t BS_FilSysType[8];
	uint8_t _reserved_1[448]; //Set to 0x00
	uint8_t Signature_word[2]; //0x55(at 510) 0xAA(at 511)
}Ext_PBP_12_16_Type;

typedef struct Ext_PBP_32  __attribute__((packed))
{
	uint32_t BPB_FATSz32;
	uint16_t BPB_ExtFlags;
	uint16_t BPB_FSVer;
	uint32_t BPB_RootClus;
	uint16_t BPB_FSInfo;
	uint16_t BPB_BkBootSec;
	uint8_t BPB_Reserved[12]; //Must be set to 0x00
	uint8_t BS_DrvNum;
	uint8_t BS_Reserved1; //Set value to 0x0
	uint8_t BS_BootSig;
	uint32_t BS_VOlID;
	uint8_t BS_VolLab[11];
	uint8_t BS_FilSysType;
	uint8_t _reserved_1[420]; //Set to 0x00
	uint8_t Signature_word[2]; //0x55(at 510) 0xAA(at 511)
}Ext_PBP_32_Type;

typedef enum FAT_TYPE
{
	FAT12,
	FAT16,
	FAT32
}FAT_TYPE;

typedef struct FSInfo __attribute__((packed))
{
	uint8_t FSI_LeadSig[4];
	uint8_t FSI_Reserved1[480];
	uint8_t FSI_StrucSig[4];
	uint8_t FSI_Free_Count[4];
	uint8_t FSI_Nxt_Free[4];
	uint8_t FSI_Reserved2[12];
	uint8_t FSI_TrailSig[4];
}FSInfo_Type;

typedef struct Dir_Struc __attribute__((packed))
{
	uint8_t DIR_Name[11];
	uint8_t DIR_Attr;
	uint8_t DIR_NTRes;
	uint8_t DIR_CtrTimeTenth;
	uint16_t DIR_CtrTIme;
	uint16_t DIR_CtrDate;
	uint16_t DIR_LstAccDate;
	uint16_t DIR_FstClusHI;
	uint16_t DIR_WriTime;
	uint16_t DIR_WritDate;
	uint16_t DIR_FstClusLO;
	uint32_t DIR_FileSize;
}Dir_Struc_Type;

#define ATTR_READ_ONLY	0x01
#define ATTR_HIDDEN	0x02
#define ATTR_SYSTEM	0x04
#define ATTR_VOLUMN_ID	0x08
#define ATTR_DIRECTORY	0x10
#define ATTR_ARCHIVE	0x20

#define ATTR_LONG_NAME 0x0f

typedef struct LongNameDirEntry __attribute__((packed))
{
	uint8_t LDIR_Ord;
	uint8_t LDIR_Name1[10];
	uint8_t LDIR_Attr;
	uint8_t LDIR_Type;
	uint8_t LDIR_Chksum;
	uint8_t LDIR_Name2[12];
	uint16_t FstClusLO; //Must be set to 0.
	uint8_t LDIR_Name3[4];
}LongNameDirEntry_Type;

typedef struct fatfs
{
	BPB_Type BPB;
	union {
		Ext_BPB_12_16_Type Ext_BPB_12_16;
		Ext_BPB_32_Type Ext_BPB_32;
	}Ext_BPB;
	
	FAT_TYPE Type;
	uint32_t RootDirSecs;
	uint32_t FATSecs;
	uint32_t FATEnSize;
	uint32_t DataSecs;
	uint32_t TotSecs;
	uint32_t CountOfClusters;
}fatfs;



void fatfs_init(fat_fs *fs);


#endif
