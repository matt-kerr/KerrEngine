// Matthew Kerr

#include "Shape.h"

using namespace std;

Shape::Shape() {
	this->type = "NONE";
	this->transform = Matrix::identity(4);
}

Shape::~Shape() { }

// copy constructor
Shape::Shape(const Shape& orig)
{
	this->transform = orig.transform;
	this->material = orig.material;
}

// move constructor
Shape::Shape(Shape&& orig) noexcept
{
	this->transform = orig.transform;
	this->material = orig.material;
}

// = operator overload
Shape& Shape::operator=(const Shape& rhs)
{
	this->transform = rhs.transform;
	this->material = rhs.material;
	return *this;
}

// move = operator overload (move assignment overload)
Shape& Shape::operator=(Shape&& orig)
{
	if (this != &orig)
	{
		this->transform = orig.transform;
		this->material = orig.material;
	}
	return *this;
}

// == operator overload
bool Shape::operator==(const Shape& rhs)
{
	return (this->material == rhs.material) && (this->transform == rhs.transform);
}