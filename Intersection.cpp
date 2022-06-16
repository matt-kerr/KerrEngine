// Matthew Kerr

#include <string>
#include <iostream>
#include <cstdarg>
#include <algorithm>
#include <vector>
#include "Intersection.h"


Intersection::Intersection()
{
	this->t = -1.0;
	this->obj = nullptr;
	this->obj_type = "NONE";
}

Intersection::~Intersection() { }

Intersection::Intersection(double t, void* obj, std::string obj_type)
{
	this->t = t;
	this->obj = obj;
	this->obj_type = obj_type;
}
// == operator overload
bool Intersection::operator==(const Intersection& rhs) { return this->t == rhs.t; }

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
	int index = -1;
	double lowest_value = 999999999.99;
	for (int i = 0; i < xs.size(); i++)
	{
		if ((xs[i].t >= 0) && (xs[i].t < lowest_value))
		{
			index = i;
			lowest_value = xs[i].t;
		}
	}
	if (index == -1)
	{
		return Intersection(-1, nullptr, "NONE");
	}	
	return xs[index];
}