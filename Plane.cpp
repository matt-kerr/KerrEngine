// Matthew Kerr

#include "Plane.h"

Plane::Plane() : Shape() { this->type = "PLANE"; }

Plane::~Plane() { }

// copy constructor
Plane::Plane(const Plane& orig) : Shape(orig) { }

// move constructor
Plane::Plane(Plane&& orig) noexcept : Shape(orig) { }

// = operator overload
Plane& Plane::operator=(const Plane& rhs)
{
	(*this) = rhs;
	return *this;
}

// move = operator overload (move assignment overload)
Plane& Plane::operator=(Plane&& orig)
{
	if (this != &orig)
	{
		(*this) = orig;
	}
	return *this;
}

// == operator overload
bool Plane::operator==(const Plane& rhs)
{
	return Shape::operator==(rhs);
}