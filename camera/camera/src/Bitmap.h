
#ifndef __aBitmapMan_h__
  #define __aBitmapMan_h__

#include <stdlib.h>
#include <stdio.h>

typedef struct BMPheader
{
	char bfType[2];  
	int bfSize;           // Tama~no en bytes del archivo (Longword)
	int reserved;
	int bfOffBits;        // Distancia en bytes desde el fin del header.. 
	int biSize;          // Tama~no del Header (40 bytes)
	int biWidth;         // Ancho de la imagen en pixeles
	int biHeight;        // Largo de la imagen en pixeles
	short int  biPlanes;        // Numero de planos de la imagen. Debe ser 1
	short int  biBitCount;      // Bits por pixel
	int  biCompression;   // Tipo de compresion
	int biSizeImage;     // Tamano en bytes de la imagen comprimida
	int biXPelsPerMeter; // Resolucion horizontal en pixeles/metros
	int biYPelsPerMeter; // Vertical horizontal en pixeles/metros
	int biClrUsed;       // Numero de colores usados
	int biClrImportant;  // Numero de colores "de importancia"
} BMPheader;

class Bitmap
{
public:
  Bitmap();
  // Default constructor

  ~Bitmap();
  // Destructor

  int SaveBMP24b(const char *filename, int w, int h, void *data);

  BMPheader m_header;
};

#endif
