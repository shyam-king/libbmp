#include "libbmp.h"

Bitmap::Bitmap(const char *filename)
{
	bmpfile.open(filename, ios::binary | ios::in | ios::out);
	if (!bmpfile)
	{
		cerr << filename << " doesnt exist\n";
	}
	else
	{
		bmpfile.read((char*)(&header), sizeof(header));
		cout << bmpfile.tellg() << endl;
		bmpfile.read((char*)(&dib), sizeof(dib));
		cout << "Height x Width: " << dib.height * dib.width << endl;
		cout << "Size: " << dib.imageSize;
	}
}

Bitmap::~Bitmap()
{
	bmpfile.close();
}

void Bitmap::draw(int x, int y)
{
	int r = dib.height;
	int c = dib.width/2;
	bmpfile.seekg(header.offset + dib.imageSize - c);
	unsigned char *row = new unsigned char[c];

	for (int i = 0; i < r; i++)
	{
		bmpfile.read((char*)row, c);
		for (int j = 0; j < c; j++)
		{
			//pixel 1
			putpixel(x + j*2, i + y, ((*(row + j)) & (240))/16);
			//pixel 2
			putpixel(x + j*2 + 1, i + y, (*(row + j)) & (15));
		}
		bmpfile.seekg(-c *  2, ios::cur);
	}
}

void Bitmap::obtainColors()
{
	palettetype pal;
	getpalette(&pal);
	bmpfile.seekg(sizeof(header) + sizeof(dib));

	ofstream file("dump.txt");

	for (int i = 0; i < pal.size; i++)
	{
		unsigned char colorData[4];
		bmpfile.read(colorData, sizeof(colorData));
		setrgbpalette(pal.colors[i], colorData[2], colorData[1], colorData[0]);
		//setrgbpalette(pal.colors[i], 0,0,0);
	}
	file.close();
}


int main()
{
	clrscr();
	Bitmap *bmp = new Bitmap("image.bmp");

	int gd = DETECT, gm;
	initgraph(&gd, &gm, "..\\BGI");
	bmp->obtainColors();
	bmp->draw(0,0);


	delete bmp;
	getch();
	closegraph();
	return 0;
}
