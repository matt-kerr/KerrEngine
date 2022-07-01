// Matthew Kerr

#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "Intersection.h"
#include "Ray.h"

class Sphere : public Shape
{
	public:
		// constructors
		Sphere();
		virtual ~Sphere();

		Sphere(const Sphere& orig); // copy constructor
		Sphere(Sphere&& orig) noexcept; // move constructor

		// operator overloads
		Sphere& operator=(const Sphere& rhs); // = operator overload
		Sphere& operator=(Sphere&& orig); // move = operator overload (move assignment overload)
		bool operator==(const Sphere& rhs); // == operator overload
};

#endif

