// Matthew Kerr

#include "color.h"

std::ostream& operator<<(std::ostream &out, const Color &c) {
	std::cout << "color(" << std::to_string(c._r) << ", " << std::to_string(c._g) << ", " << std::to_string(c._b) << ")" << std::endl;
	return out;
}

Color::Color() {
	_r = 0.0;
	_g = 0.0;
	_b = 0.0;
}
Color::Color(const double& r, const double& g, const double& b) {
	_r = r;
	_g = g;
	_b = b;
}

bool operator==(const Color &lhs, const Color &rhs) {
	return almost_equal(lhs._r, rhs._r) && almost_equal(lhs._g, rhs._g) && almost_equal(lhs._b, rhs._b);
}

Color operator+(const Color &c1, const Color &c2) {
	return Color(c1._r + c2._r, c1._g + c2._g, c1._b + c2._b);
}

Color operator-(const Color &c1, const Color &c2) {
	return Color(c1._r - c2._r, c1._g - c2._g, c1._b - c2._b);
}

Color operator*(const Color &c1, const Color &c2) {
	return Color(c1._r * c2._r, c1._g * c2._g, c1._b * c2._b);
}

Color operator*(const Color &c, const double &scalar) {
	return Color(c._r * scalar, c._g * scalar, c._b * scalar);
}

double random_color_double() {
	return ((double)rand() / (double)RAND_MAX * 0.7) + 0.3;
}

Color random_color() {
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;
	while ((r > 0.8 && g > 0.8 && b > 0.8) // too bright
		|| (std::abs(r - g) < 0.1 && std::abs(r - b) < 0.1 && std::abs(g - b) < 0.1)) { // too similar = grey
		r = random_color_double();
		g = random_color_double();
		b = random_color_double();
	}
	return Color(r, g, b);
}