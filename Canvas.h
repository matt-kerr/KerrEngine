// Matthew Kerr

#ifndef CANVAS_H
#define CANVAS_H

#include <fstream>
#include <vector>
#include "Color.h"

class Canvas
{
	public:
		int width;
		int height;
		std::vector<std::vector<Color>> data;
		Canvas(const int& width, const int& height);
		virtual ~Canvas();
		void writePixel(const int& row, const int& col, const Color& c);
		Color pixelAt(const int& row, const int& col);
		void saveImage(std::ofstream& fout, const int& scalar);
};

#endif;