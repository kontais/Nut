#ifndef _GLYPHBDF_H_
#define _GLYPHBDF_H_

struct Glyph_BDF{
		unsigned char ENCODIN;//ENCODING is followed by a positive integer representing the Adobe Standard Encoding value
		unsigned char BITMAP[16][2];//BITMAP introduces the hexadecimal data for the character bitmap
		unsigned int  File_offset[4];
};
typedef struct Glyph_BDF GlyphBDF;
typedef GlyphBDF * BDF;

void Glyph_BDF_init(BDF Glyph_BDF);
void GetBitmapFromGlyphBDF(unsigned char **stream,BDF Glyph_BDF,unsigned char Glyph);
void file_seek(unsigned char **stream, unsigned int offset);






#endif

/*********************end file******************/

