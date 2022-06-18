// Matthew Kerr

#include <fstream>
#include <string>
#include "Canvas.h"
#include "Color.h"
using namespace std;

Canvas::Canvas(const int& width, const int& height)
{
	this->width = width;
	this->height = height;
	this->data.resize(height, vector<Color>(width));
}

Canvas::~Canvas() { }

void Canvas::writePixel(const int& x, const int& y, const Color& c)
{
	this->data[y][x].r = c.r;
	this->data[y][x].g = c.g;
	this->data[y][x].b = c.b;
}

Color Canvas::pixelAt(const int& x, const int& y)
{
	return this->data[x][y];
}

void Canvas::saveImage(ofstream& fout, const int& scalar)
{
	int count = 0;
	fout << "P3" << endl;
	fout << this->width << " " << this->height << endl;
	fout << 255 << endl;
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			fout << std::round(max(0.0, (min(1.0, this->data[i][j].r) * scalar))) << " "
				 << std::round(max(0.0, (min(1.0, this->data[i][j].g) * scalar))) << " "
				 << std::round(max(0.0, (min(1.0, this->data[i][j].b) * scalar)));
			count++;
			if (j < this->width - 1)
			{
				if (count < 6)
				{
					fout << " ";
				}
				else
				{
					fout << endl;
					count = 1;
				}
			}
		}
		fout << endl;
		count = 1;
	}
}
