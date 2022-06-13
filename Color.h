// Mathew Kerr

#ifndef COLOR_H
#define COLOR_H
#include <iostream>
using namespace std;

class Color
{
	friend istream& operator>>(istream& in, Color& c);
	friend ostream& operator<<(ostream& out, const Color& c);

	public:
		double red;
		double green;
		double blue;
		Color();
		Color(const double& red, const double& green, const double& blue);
		virtual ~Color();
		Color& operator=(const Color& c2);
		Color operator+(const Color& c2) const;
		Color operator-(const Color& c2) const;
		Color operator*(const Color& c2) const;
		Color operator*(const double& scalar) const;
		static Color create(const double& red, const double& green, const double& blue);
};

#endif