#ifndef _MBR_H_
#define _MBR_H_

typedef struct Partition_Entry
{
	uint8_t Status;
	uint8_t CHS_Addr_Fist[3];
	uint8_t Partition_Type;
	uint8_t CHS_Addr_Last[3];
	uint8_t LBA_First[4];
	uint8_t Num_Of_Sec[4];
}Partition_Entry;

typedef struct MBR_Record
{
	uint8_t Boot_Code[446];
	Partition_Entry Part_Entry[4];
	uint8_t BootSig[2];
}MBR_Record;


void MBR_Init(MBR_Record *record);

#endif
