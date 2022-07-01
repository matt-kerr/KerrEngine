// Matthew Kerr

#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

class Plane : public Shape
{
    public:
        Plane();
		virtual ~Plane();

		Plane(const Plane& orig); // copy constructor
		Plane(Plane&& orig) noexcept; // move constructor

		// operator overloads
		Plane& operator=(const Plane& rhs); // = operator overload
		Plane& operator=(Plane&& orig); // move = operator overload (move assignment overload)
		bool operator==(const Plane& rhs); // == operator overload
};

#endif