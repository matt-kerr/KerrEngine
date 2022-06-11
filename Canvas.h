// Matthew Kerr

#ifndef CANVAS_H
#define CANVAS_H

#include <string>
#include "Color.h"
using namespace std;

class Canvas
{
	public:
		int width;
		int height;
		Color ** data;
		Canvas(const int& width, const int& height);
		virtual ~Canvas();
		void writePixel(const int& row, const int& col, const Color& c);
		Color pixelAt(const int& row, const int& col);
		void saveImage(ofstream& fout, const int& scalar);
};

#endif;