// Matthew Kerr

#include "Sphere.h"

Sphere::Sphere() : Shape()
{
	this->type = "SPHERE";
}

Sphere::~Sphere() { }

// copy constructor
Sphere::Sphere(const Sphere& orig) : Shape(orig) { }

// move constructor
Sphere::Sphere(Sphere&& orig) noexcept : Shape(orig) { }

// = operator overload
Sphere& Sphere::operator=(const Sphere& rhs)
{
	(*this) = rhs;
	return *this;
}

// move = operator overload (move assignment overload)
Sphere& Sphere::operator=(Sphere&& orig)
{
	if (this != &orig)
	{
		(*this) = orig;
	}
	return *this;
}

// == operator overload
bool Sphere::operator==(const Sphere& rhs)
{
	return Shape::operator==(rhs);
	//return this->transform == rhs.transform && this->material == rhs.material;
}