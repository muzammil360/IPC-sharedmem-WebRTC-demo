#include "Bitmap.h"
#include <string.h>

Bitmap::Bitmap()
{
	memset(&m_header, 0, sizeof (m_header));
}

Bitmap::~Bitmap()
{

}

int Bitmap::SaveBMP24b(const char *filename, int w, int h, void *data)
{
	FILE *f;

	f = fopen(filename, "wb");
	if (f == NULL)
		return 1;

	m_header.bfType[0] ='B'; 
	m_header.bfType[1] = 'M'; 
	m_header.bfOffBits=54;	// + nothing because there is not palette
	m_header.biSize=40;
	m_header.biWidth=w;
	m_header.biHeight=h;
	m_header.biPlanes=1;
	m_header.biBitCount=24;
	m_header.biCompression=0; 
	m_header.biSizeImage=0;
	m_header.biXPelsPerMeter=0;
	m_header.biYPelsPerMeter=0;
	m_header.biClrUsed=0;
	m_header.biClrImportant=0;
	int lineWidth = m_header.biWidth*3;
	if (lineWidth & 3)
		lineWidth += 4-(lineWidth & 3);
	m_header.biSizeImage = lineWidth * m_header.biHeight;
	m_header.bfSize = m_header.bfOffBits + m_header.biSizeImage;	

	if (fwrite(m_header.bfType, 2, 1, f) != 1)
	{
		fclose(f);
		return 2;
	}
	if (fwrite(&m_header.bfSize, 52, 1, f) != 1)
	{
		fclose(f);
		return 2;
	}


	if (fwrite(data, 1, m_header.biSizeImage, f) != m_header.biSizeImage)
	{
		fclose(f);
		return 3;
	}
	fclose(f);
	return 0;
}
