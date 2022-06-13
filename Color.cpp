// Matthew Kerr

#include <iostream>
#include "Color.h"
#include "KerrEngineException.h"
using namespace std;

istream& operator>>(istream& in, Color& c)
{
	throw KerrEngineException(EXCEPTION_NO_COLOR_INPUT_REDIRECT);
	return in;
}
ostream& operator<<(ostream& out, const Color& c)
{
	cout << "(" << std::to_string(c.red) << ", " + std::to_string(c.green) << ", " << std::to_string(c.blue) << ")";
	return out;
}

Color::Color()
{
	this->red = 0.0;
	this->green = 0.0;
	this->blue = 0.0;
}
Color::Color(const double& red, const double& green, const double& blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

Color::~Color() {}

Color& Color::operator=(const Color& c2)
{
	this->red = c2.red;
	this->green = c2.green;
	this->blue = c2.blue;
	return *this;
}

Color Color::operator+(const Color& c2) const
{
	Color c1 = *this;
	Color result((c1.red + c2.red), (c1.green + c2.green), (c1.blue + c2.blue));
	return result;
}

Color Color::operator-(const Color& c2) const
{
	Color c1 = *this;
	Color result((c1.red - c2.red), (c1.green - c2.green), (c1.blue - c2.blue));
	return result;
}

Color Color::operator*(const Color& c2) const
{
	Color c1 = *this;
	Color result((c1.red * c2.red), (c1.green * c2.green), (c1.blue * c2.blue));
	return result;
}

Color Color::operator*(const double& scalar) const
{
	Color c1 = *this;
	Color result((c1.red * scalar), (c1.green * scalar), (c1.blue * scalar));
	return result;
}

Color Color::create(const double& red, const double& green, const double& blue)
{
	Color result(red, green, blue);
	return result;
}