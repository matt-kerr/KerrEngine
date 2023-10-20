// Matthew Kerr

#include "canvas.h"

Canvas::Canvas(const int &w, const int &h) {
	_w = w;
	_h = h;
	_rendered = 0;
	_area = _w * _h;
	_data = (double *)calloc(sizeof(double), _w * _h * 3);
}

Canvas::~Canvas() { free(_data); }

Color Canvas::pixel_at(const int& x, const int& y) {
	int index = pixel_to_index(x, y);
	double r = _data[index++];
	double g = _data[index++];
	double b = _data[index++];
	return Color(r, g, b);
}

void Canvas::write_pixel(const int& x, const int& y, const Color &c) {
	std::unique_lock<std::mutex> guard(_mutex);
	int index = pixel_to_index(x, y);
	_data[index++] = c._r;
	_data[index++] = c._g;
	_data[index++] = c._b;
	_rendered++;
	if (_rendered % 100 == 0) { std::cout << std::to_string(_rendered) << "/" << std::to_string(_area) << " " << ((float)_rendered / (float)_area) * 100.0 << "%" << std::endl; }
}

void Canvas::save_image(std::ofstream& fout, const int& scalar) {
	int count = 0;
	int index = 0;
	fout << "P3" << std::endl;
	fout << _w << " " << _h << std::endl;
	fout << 255 << std::endl;
	for (int i = 0; i < _h; i++) {
		for (int j = 0; j < _w; j++) {
			fout << std::round(std::max(0.0, (std::min(1.0, _data[index++]))) * scalar) << " ";
			fout << std::round(std::max(0.0, (std::min(1.0, _data[index++]))) * scalar) << " ";
			fout << std::round(std::max(0.0, (std::min(1.0, _data[index++]))) * scalar);
			count++;
			if (j < _w - 1) {
				if (count < 6) {
					fout << " ";
				}
				else {
					fout << std::endl;
					count = 1;
				}
			}
		}
		fout << std::endl;
		count = 1;
	}
}
