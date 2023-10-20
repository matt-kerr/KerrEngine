// Mathew Kerr

#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <string>
#include <ctime>

#include "../kerr_inline.h"

class Color
{
	friend std::ostream& operator<<(std::ostream &out, const Color &c);

	public:
		double _r;
		double _g;
		double _b;

		Color();
		Color(const double &r, const double &g, const double &b);
		virtual ~Color() = default;
};

bool operator==(const Color &lhs, const Color &rhs);
Color operator+(const Color &c1, const Color &c2);
Color operator-(const Color &c1, const Color &c2);
Color operator*(const Color &c1, const Color &c2);
Color operator*(const Color &c, const double &scalar);

inline Color white() { return Color(1.0, 1.0, 1.0); }
inline Color black() { return Color(0.0, 0.0, 0.0); }
double random_color_double();
Color random_color();

#endif