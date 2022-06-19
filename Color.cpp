// Matthew Kerr

#include <iostream>
#include "Color.h"
#include "KerrEngineException.h"
using namespace std;

istream& operator>>(istream& in, Color& c)
{
	throw KerrEngineException("EXCEPTION_NO_COLOR_INPUT_REDIRECT");
	return in;
}
ostream& operator<<(ostream& out, const Color& c)
{
	cout << "color(" << std::to_string(c.r) << ", " + std::to_string(c.g) << ", " << std::to_string(c.b) << ")" << endl;
	return out;
}

Color::Color()
{
	this->r = 0.0;
	this->g = 0.0;
	this->b = 0.0;
}
Color::Color(const double& r, const double& g, const double& b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

Color::~Color() {}

// copy constructor
Color::Color(const Color& orig)
{
	this->r = orig.r;
	this->g = orig.g;
	this->b = orig.b;
}

// move constructor
Color::Color(Color&& orig) noexcept
{
	this->r = orig.r;
	this->g = orig.g;
	this->b = orig.b;
}

Color& Color::operator=(const Color& c2)
{
	this->r = c2.r;
	this->g = c2.g;
	this->b = c2.b;
	return *this;
}

Color& Color::operator=(Color&& orig)
{
	this->r = orig.r;
	this->g = orig.g;
	this->b = orig.b;
	return *this;
}

bool Color::operator==(const Color& rhs)
{
	return ((this->r == rhs.r) && (this->g == rhs.g) && (this->b == rhs.b));
}

Color Color::operator+(const Color& c2) const
{
	return Color::create((this->r + c2.r), (this->g + c2.g), (this->b + c2.b));
}

Color Color::operator-(const Color& c2) const
{
	return Color::create((this->r - c2.r), (this->g - c2.g), (this->b - c2.b));
}

Color Color::operator*(const Color& c2) const
{
	return Color::create((this->r * c2.r), (this->g * c2.g), (this->b * c2.b));
}

Color Color::operator*(const double& scalar) const
{
	return Color::create((this->r * scalar), (this->g * scalar), (this->b * scalar));
}

Color Color::create(const double& red, const double& green, const double& blue)
{
	Color result(red, green, blue);
	return result;
}