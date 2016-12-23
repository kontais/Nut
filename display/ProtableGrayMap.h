#ifndef _PROTABLEGRAYMAP_H_
#define _PROTABLEGRAYMAP_H_
//#include "stdio.h"

#define Max_range 48
#define Max_line 128
typedef struct ProtableGreyMap{
	
	unsigned char Magic;//magic number identifies the type of file it is(PBM,PGM,and PPM)and its encoding(ASCII or binary)
	int Max_value;
	int X_axis;
	int Y_axis;
	unsigned char ASIIC_versions[16][8];//bitmap of Glyph
}ProtableGrayMap;

//typedef struct ProtableGreyMap ProtableGreyMap;
typedef  struct ProtableGreyMap * PGM;

//unsigned char PGMBuffer[Max_range*32][Max_line*16];//the buffer of the file.pgm


void ProtableGrayMapASIIC_Init(PGM PGM_Map,int width,int high,unsigned char Glyph);
//int WritePGMHeader(FILE *stream,PGM PGM_Map);
void WritePGMBufferInit(PGM PGM_Map,int max_range,int max_line);
//void UpdataPGMBuffer(FILE* stream,PGM PGM_Map);
void WritePGMData(PGM PGM_Map,int range,int line);
void DisplayInit(void );
void Display(void);

#endif


/**************************endfile************************/

