// Matthew Kerr

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <string>
#include <iostream>
#include <cstdarg>
#include <algorithm>
#include <vector>
#include "Intersection.h"
#include "Sphere.h"
using namespace std;

class Intersection
{
	public:
		double t;
		Sphere obj;
		
		Intersection();
		virtual ~Intersection();
		Intersection(double t, Sphere obj);
		bool operator==(const Intersection& rhs); // == operator overload
		bool operator<(const Intersection& rhs); // < operator overload
		bool operator>(const Intersection& rhs); // > operator overload
		static std::vector<Intersection> intersections(int count, Intersection params ...);
		static std::vector<Intersection> intersections(int count, std::vector<Intersection> params ...);
		static Intersection hit(std::vector<Intersection> xs);
};

#endif;