// Matthew Kerr

#include "Intersection.h"

Intersection::Intersection()
{
	this->t = -999.0;
	this->obj = nullptr;
}

Intersection::~Intersection() { }

Intersection::Intersection(double t, Shape* obj)
{
	this->t = t;
	this->obj = obj;
}
// == operator overload
bool Intersection::operator==(const Intersection& rhs) { return KerrEngine::almost_equal(this->t, rhs.t); }

// < operator overload
bool Intersection::operator<(const Intersection& rhs) { return this->t < rhs.t; }

// > operator overload
bool Intersection::operator>(const Intersection& rhs) { return this->t > rhs.t; }

std::vector<Intersection> Intersection::intersections(int count, Intersection params ...)
{
	std::vector<Intersection> ret;
	va_list args;
	va_start(args, count);
	for (int i = 0; i < count; i++)
	{
		ret.push_back(va_arg(args, Intersection));
	}
	std::sort(ret.begin(), ret.end());
	return ret;
}

std::vector<Intersection> Intersection::intersections(int count, std::vector<Intersection> params ...)
{
	std::vector<Intersection> ret;
	va_list args;
	va_start(args, count);
	for (int i = 0; i < count; i++)
	{
		std::vector<Intersection> curr = va_arg(args, std::vector<Intersection>);
		for (int j = 0; j < curr.size(); j++)
		{
			ret.push_back(curr[j]);
		}
	}
	std::sort(ret.begin(), ret.end());
	return ret;
}


Intersection Intersection::hit(std::vector<Intersection> xs)
{
	// list must be sorted
	for (int i = 0; i < xs.size(); i++)
	{
		if (xs[i].t > 0)
		{
			return xs[i];
		}
	}
	// no hit
	return Intersection(0.0, nullptr);
}