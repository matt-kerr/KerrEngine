// Matthew Kerr

#ifndef CANVAS_H
#define CANVAS_H

#include <cstdlib>
#include <fstream>
#include <vector>
#include <mutex>

#include "../primitives/color.h"

class Color;
class Canvas
{
	public:
		int _w;
		int _h;
		int _rendered;
		int _area;
		double *_data;
		std::mutex _mutex;

		Canvas() { throw std::invalid_argument("Canvas requires parameters"); }
		Canvas(const int &w, const int &h);
		virtual ~Canvas();

		Color pixel_at(const int &x, const int &y);
		void write_pixel(const int &x, const int &y, const Color &c);
		void save_image(std::ofstream& fout, const int& scalar);
	private:
		inline int pixel_to_index(const int &x, const int &y) const { return 3 * (x + y * _w); }
};

#endif;