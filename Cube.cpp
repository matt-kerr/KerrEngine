// Matthew Kerr

#include "Cube.h"

Cube::Cube() : Shape() { this->type = "CUBE"; }

Cube::~Cube() { }

// copy constructor
Cube::Cube(const Cube& orig) : Shape(orig) { }

// move constructor
Cube::Cube(Cube&& orig) noexcept : Shape(orig) { }

// = operator overload
Cube& Cube::operator=(const Cube& rhs)
{
	(*this) = rhs;
	return *this;
}

// move = operator overload (move assignment overload)
Cube& Cube::operator=(Cube&& orig)
{
	if (this != &orig)
	{
		(*this) = orig;
	}
	return *this;
}

// == operator overload
bool Cube::operator==(const Cube& rhs)
{
	return Shape::operator==(rhs);
}