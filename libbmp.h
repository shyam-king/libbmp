#ifndef LIBBMP_H
#define LIBBMP_H

#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<fstream.h>

class Bitmap {
	fstream bmpfile;

	public:
	struct  {
		char sign[2];
		unsigned long int size;
		char res[4];
		unsigned long int offset;
	} header;

	struct {
		unsigned long int headerSize;
		signed long int width;
		signed long int height;
		int colorPanes;
		int bpp;
		unsigned long int compMethod;
		unsigned long int imageSize;
		unsigned long res[2];
		unsigned long numColors;
		unsigned long numImpColors;
	} dib;

	Bitmap(const char*);
	~Bitmap();

	void draw(int x, int y);
	void obtainColors();
};

#endif
