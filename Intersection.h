// Matthew Kerr

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include <cstdarg>
#include <algorithm>
#include <vector>

#include "Shape.h"
#include "KerrEngineException.h"
class Shape;
class Intersection
{
	public:
		double t;
		Shape* obj;
		
		Intersection();
		virtual ~Intersection();
		Intersection(double t, Shape* obj);
		bool operator==(const Intersection& rhs); // == operator overload
		bool operator<(const Intersection& rhs); // < operator overload
		bool operator>(const Intersection& rhs); // > operator overload
		static std::vector<Intersection> intersections(int count, Intersection params ...);
		static std::vector<Intersection> intersections(int count, std::vector<Intersection> params ...);
		static Intersection hit(std::vector<Intersection> xs);
};

#endif;