// Matthew Kerr

#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

#include "Matrix.h"
#include "Shape.h"

class Computations
{
	public:
		double t;
		Shape* obj;
		Matrix point;
		Matrix over_point;
		Matrix eyev;
		Matrix normalv;
		bool inside;
		
		// constructors
		Computations();
		virtual ~Computations();
		Computations(double t, Shape* obj, Matrix point, Matrix over_point, Matrix eyev, Matrix normalv, bool inside);
		Computations(const Computations& orig); // copy constructor
		Computations(Computations&& orig); // move constructor

		// operator overloads
		Computations& operator=(const Computations& rhs); // = operator overload
		Computations& operator=(Computations&& orig); // move = operator overload (move assignment overload)
};

#endif