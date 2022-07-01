// Mathew Kerr

#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <string>
#include "KerrEngine.h"
#include "KerrEngineException.h"
using namespace std;

class Color
{
	friend istream& operator>>(istream& in, Color& c);
	friend ostream& operator<<(ostream& out, const Color& c);

	public:
		double r;
		double g;
		double b;

		// constructors
		Color();
		Color(const double& r, const double& g, const double& b);
		virtual ~Color();
		Color(const Color& orig); // copy constructor
		Color(Color&& orig); // move constructor

		// operator overloads
		Color& operator=(const Color& c2); // = operator overload
		Color& operator=(Color&& orig); // move = operator overload (move assignment overload)
		bool operator==(const Color& rhs); // == operator overload
		Color operator+(const Color& c2) const;
		Color operator-(const Color& c2) const;
		Color operator*(const Color& c2) const;
		Color operator*(const double& scalar) const;
};

#endif