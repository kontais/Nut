#include "ProtableGrayMap.h"
#include "GlyphBDF.h"
#include "fat.h"
#include "klibc.h"

unsigned char PGMBuffer[Max_range*32][Max_line*16];

/**
	*function:get the bitmap of Glyph to PGM map
	*
	*
	*/
void PGM_ASIIC_versionsInit(PGM PGM_Map,unsigned char Glyph){
	
	FATFS_Type fs;
	fatfs_init(&fs);
	unsigned char *buf = malloc(40960);
	unsigned char *stream =buf;
	memset(buf, 0, 40960);
	read_file(&fs,"unifont-asiic.bdf",buf,40960);
	
	GlyphBDF Glyph_BDF;
	Glyph_BDF_init(&Glyph_BDF);
	GetBitmapFromGlyphBDF(&stream,&Glyph_BDF,Glyph);
	
	for(int i=0;i<16;i++)
		for(int j=0; j<8; j++)
			PGM_Map->ASIIC_versions[i][j]=0;
		
	for(int i=0;i<16;i++)
		for(int j=0;j<2;j++){
			
			switch(Glyph_BDF.BITMAP[i][j]){
				case '0':break;
				
				case '1':{
					if(j==0)
						PGM_Map->ASIIC_versions[i][3]=255;
					else 
						PGM_Map->ASIIC_versions[i][7]=255;
					break;
				}
				
				case '2':{
					if(j==0)
						PGM_Map->ASIIC_versions[i][2]=255;
					else
						PGM_Map->ASIIC_versions[i][6]=255;
					break;
					
				}
				
				case '3':{
					if(j==0){
						PGM_Map->ASIIC_versions[i][3]=255;
						PGM_Map->ASIIC_versions[i][2]=255;
					}
					else{
						PGM_Map->ASIIC_versions[i][7]=255;
						PGM_Map->ASIIC_versions[i][6]=255;
					}
					break;
				}
					
				case '4':{
					if(j==0)
						PGM_Map->ASIIC_versions[i][1]=255;
					else 
						PGM_Map->ASIIC_versions[i][5]=255;
					break;
				}
				
				case '5':{
					if(j==0){
						PGM_Map->ASIIC_versions[i][3]=255;
						PGM_Map->ASIIC_versions[i][1]=255;
					}
					else{
						PGM_Map->ASIIC_versions[i][7]=255;
						PGM_Map->ASIIC_versions[i][5]=255;
					}
					break;
				}
				
				case '6':{
					if(j==0){
						PGM_Map->ASIIC_versions[i][2]=255;
						PGM_Map->ASIIC_versions[i][1]=255;
					}
					else{
						PGM_Map->ASIIC_versions[i][6]=255;
						PGM_Map->ASIIC_versions[i][5]=255;
					}
					break;	
				}
				
				case '7':{
					if(j==0){
						PGM_Map->ASIIC_versions[i][3]=255;
						PGM_Map->ASIIC_versions[i][2]=255;
						PGM_Map->ASIIC_versions[i][1]=255;
					}
					else{
						PGM_Map->ASIIC_versions[i][7]=255;
						PGM_Map->ASIIC_versions[i][6]=255;
						PGM_Map->ASIIC_versions[i][5]=255;
					}
					break;
				}
				
				case '8':{
					if(j==0)
						PGM_Map->ASIIC_versions[i][0]=255;
					else
						PGM_Map->ASIIC_versions[i][4]=255;
					break;
				}
				
				case '9':{
					if(j==0){
						PGM_Map->ASIIC_versions[i][3]=255;
						PGM_Map->ASIIC_versions[i][0]=255;
					}
					else{
						PGM_Map->ASIIC_versions[i][7]=255;
						PGM_Map->ASIIC_versions[i][4]=255;
					}
					break;
				}
				
				case 'A':{
					
					if(j==0){
						PGM_Map->ASIIC_versions[i][2]=255;
						PGM_Map->ASIIC_versions[i][0]=255;
					}
					else{
						PGM_Map->ASIIC_versions[i][6]=255;
						PGM_Map->ASIIC_versions[i][4]=255;
					}
					break;
				}
				 
				case 'B':{
					
					if(j==0){
						PGM_Map->ASIIC_versions[i][3]=255;
						PGM_Map->ASIIC_versions[i][2]=255;
						PGM_Map->ASIIC_versions[i][0]=255;
					}
					else{
						PGM_Map->ASIIC_versions[i][7]=255;
						PGM_Map->ASIIC_versions[i][6]=255;
						PGM_Map->ASIIC_versions[i][4]=255;
					}
					break;
				}
				
				case 'C':{
					
					if(j==0){
						PGM_Map->ASIIC_versions[i][1]=255;
						PGM_Map->ASIIC_versions[i][0]=255;
					}
					else{
						PGM_Map->ASIIC_versions[i][5]=255;
						PGM_Map->ASIIC_versions[i][4]=255;
					}
					break;
				}
				
				case 'D':{
					
					if(j==0){
						PGM_Map->ASIIC_versions[i][3]=255;
						PGM_Map->ASIIC_versions[i][1]=255;
						PGM_Map->ASIIC_versions[i][0]=255;
					}
					else{
						PGM_Map->ASIIC_versions[i][7]=255;
						PGM_Map->ASIIC_versions[i][5]=255;
						PGM_Map->ASIIC_versions[i][4]=255;
					}
					break;
				}
				
				case 'E':{
					
					if(j==0){
						PGM_Map->ASIIC_versions[i][2]=255;
						PGM_Map->ASIIC_versions[i][1]=255;
						PGM_Map->ASIIC_versions[i][0]=255;
					}
					else{
						PGM_Map->ASIIC_versions[i][6]=255;
						PGM_Map->ASIIC_versions[i][5]=255;
						PGM_Map->ASIIC_versions[i][4]=255;
					}
					break;
				}
				
				case 'F':{
					
					if(j==0){
						PGM_Map->ASIIC_versions[i][3]=255;
						PGM_Map->ASIIC_versions[i][2]=255;
						PGM_Map->ASIIC_versions[i][1]=255;
						PGM_Map->ASIIC_versions[i][0]=255;
					}
					else{
						PGM_Map->ASIIC_versions[i][7]=255;
						PGM_Map->ASIIC_versions[i][6]=255;
						PGM_Map->ASIIC_versions[i][5]=255;
						PGM_Map->ASIIC_versions[i][4]=255;
					}
					break;
				}
				
				default: ;
				
			}
		}
}

/**
	*function:initialization the struct of PGM map
	*
	*
	*/
void ProtableGrayMapASIIC_Init(PGM PGM_Map,int width,int high,unsigned char Glyph){
	
	PGM_Map->Max_value=20;
	PGM_Map->Magic=2;
	PGM_Map->X_axis=width;
	PGM_Map->Y_axis=high;
	PGM_ASIIC_versionsInit(PGM_Map,Glyph);
	
}

/**
	*function:write the data to the header of file.pgm 
	*
	*
	*/
/*int WritePGMHeader(FILE *stream,PGM PGM_Map){
	
	   if (stream==NULL) 80000008{  
        printf("FILE error\n");  
        exit(3);  
    }  
  
    switch(PGM_Map->Magic){
    
    	case 1:{
    	
    		fprintf(stream,"P1\n");	
    		break;
    	}	
    	case 2:	{
    	
    		fprintf(stream,"P2\n");	
    		break;
    	}
    	case 3:{
    	
    		fprintf(stream,"P3\n");	
    		break;
    	}	
    	case 4:{
    	
    		fprintf(stream,"P4\n");	
    		break;
    	}	
    	case 5:{
    	
    		fprintf(stream,"P5\n");	
    		break;
    	}	
    	case 6:{
    	
    		fprintf(stream,"P6\n");	
    		break;
    	}	
    	default :	exit(4);
    }
    
    fprintf(stream,"%d,%d\n",PGM_Map->X_axis,PGM_Map->Y_axis);
    fprintf(stream,"%d\n",PGM_Map->Max_value);
    
    return 1;  
}*/

/**
	*function:write the data to file.gpm
	*
	*
	*/
void WritePGMData(PGM PGM_Map,int range,int line) {  
    
    for(int i=0;i<16;i++) {   // every rwo 
     			
        for(int j=0;j<8;j++) {   // every line 
        		
        		PGMBuffer[range*32+2*i][line*16+2*j]=PGM_Map->ASIIC_versions[i][j];
        		PGMBuffer[range*32+2*i][line*16+2*j+1]=PGM_Map->ASIIC_versions[i][j];
        } 
        for(int j=0;j<8;j++) {   // every line  
        
        	PGMBuffer[range*32+2*i+1][line*16+2*j]=PGM_Map->ASIIC_versions[i][j];
        	PGMBuffer[range*32+2*i+1][line*16+2*j+1]=PGM_Map->ASIIC_versions[i][j];	 
        } 
    }
    
} 
/**
	*
	*
	*/
void WritePGMBufferInit(PGM PGM_Map,int max_range,int max_line){
	
	ProtableGrayMapASIIC_Init(PGM_Map,max_line*16,max_range*32,' ');
	for(int i=0;i<max_range;i++)
		for(int j=0;j<max_line;j++)
			WritePGMData(PGM_Map,i,j);
} 
/**
	*
	*
	*
	*/
void DisplayInit(void ){
	
	ProtableGrayMap PGM_Map;
	WritePGMBufferInit(&PGM_Map,Max_range,Max_line);
	
	ProtableGrayMapASIIC_Init(&PGM_Map,Max_line*16,Max_range*32,'H');
	WritePGMData(&PGM_Map,10,40);
	ProtableGrayMapASIIC_Init(&PGM_Map,Max_line*16,Max_range*32,'e');
	WritePGMData(&PGM_Map,10,41);
	ProtableGrayMapASIIC_Init(&PGM_Map,Max_line*16,Max_range*32,'l');
	WritePGMData(&PGM_Map,10,42);
	WritePGMData(&PGM_Map,10,43);
	WritePGMData(&PGM_Map,10,49);
	ProtableGrayMapASIIC_Init(&PGM_Map,Max_line*16,Max_range*32,'o');
	WritePGMData(&PGM_Map,10,44);
	WritePGMData(&PGM_Map,10,48);
	ProtableGrayMapASIIC_Init(&PGM_Map,Max_line*16,Max_range*32,'w');
	WritePGMData(&PGM_Map,10,46);
	ProtableGrayMapASIIC_Init(&PGM_Map,Max_line*16,Max_range*32,'r');
	WritePGMData(&PGM_Map,10,47);
	ProtableGrayMapASIIC_Init(&PGM_Map,Max_line*16,Max_range*32,'d');
	WritePGMData(&PGM_Map,10,50);
	
}

void Display(void){

	
	DisplayInit();
	uint32_t *ptr = (uint32_t *)0x80000000;
	for(int i=0;i<Max_range*32;i++){
	
		for(int j=0;j<Max_line*16;j++){
		
			ptr[i*Max_line*16+j]=PGMBuffer[i][j]*16*16*16*16*16*16+PGMBuffer[i][j]*16*16*16*16+PGMBuffer[i][j]*16*16+PGMBuffer[i][j];
			
		}
	
	}

}


/**
	*function:initialzation the file.pgm buffer
	*
	*
	*/

/*void WritePGMBufferInit(FILE* stream,PGM PGM_Map,int max_range,int max_line){
	
	ProtableGrayMapASIIC_Init(PGM_Map,max_line*16,max_range*32,' ');
	WritePGMHeader(stream,PGM_Map);
	fgetpos(stream,&(PGM_Map->pos));
	for(int i=0;i<max_range;i++)
		for(int j=0;j<max_line;j++)
			WritePGMData(PGM_Map,i,j);
}*/
/**
	*write the buffer data to the file.pgm
	*
	*/
/*void UpdataPGMBuffer(FILE* stream,PGM PGM_Map){
	
	fsetpos(stream,&(PGM_Map->pos));
	for(int i=0;i<Max_range*32;i++){
	
		for(int j=0;j<Max_line*16;j++){
			if(!PGMBuffer[i][j])
				fprintf(stream," %d ",PGMBuffer[i][j]);
			else
				fprintf(stream,"%d ",PGMBuffer[i][j]);
		}
		fprintf(stream,"\n");
	}
	

}*/




/******************end file*********************/

