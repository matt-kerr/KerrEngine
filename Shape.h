// Matthew Kerr

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "Matrix.h"
#include "Material.h"

class Shape
{
    public:
		std::string type;
        Matrix transform;
        Material material;

		// constructors
		Shape();
		virtual ~Shape();

		Shape(const Shape& orig); // copy constructor
		Shape(Shape&& orig) noexcept; // move constructor

		// operator overloads
		Shape& operator=(const Shape& rhs); // = operator overload
		Shape& operator=(Shape&& orig); // move = operator overload (move assignment overload)
		bool operator==(const Shape& rhs); // == operator overload
};

#endif