// Matthew Kerr

#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

class Cube : public Shape
{
    public:
        Cube();
        virtual ~Cube();

        Cube(const Cube& orig); // copy constructor
		Cube(Cube&& orig) noexcept; // move constructor

		// operator overloads
		Cube& operator=(const Cube& rhs); // = operator overload
		Cube& operator=(Cube&& orig); // move = operator overload (move assignment overload)
		bool operator==(const Cube& rhs); // == operator overload
};

#endif