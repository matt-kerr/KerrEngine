// Matthew Kerr

#include <iostream>
#include <cstdarg>
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

Intersection* Intersection::intersections(int count, Intersection params ...)
{
	va_list args;
	va_start(args, count);
	Intersection* result = new Intersection[count];
	for (int i = 0; i < count; i++)
	{
		result[i] = va_arg(args, Intersection);
	}
	return result;
}


Intersection Intersection::hit(int count, Intersection* xs)
{
	int index = -1;
	double lowest_value = 999999999.99;
	for (int i = 0; i < count; i++)
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