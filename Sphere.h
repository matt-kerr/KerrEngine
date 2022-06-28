// Matthew Kerr

#ifndef SPHERE_H
#define SPHERE_H

#include "Matrix.h"
#include "Material.h"
#include "KerrEngineException.h"
using namespace std;

class Sphere
{
public:
	Matrix transform;
	Material material;

	// constructors
	Sphere();
	virtual ~Sphere();

	Sphere(const Sphere& orig); // copy constructor
	Sphere(Sphere&& orig) noexcept; // move constructor

	// operator overloads
	Sphere& operator=(const Sphere& rhs); // = operator overload
	Sphere& operator=(Sphere&& orig); // move = operator overload (move assignment overload)
	bool operator==(const Sphere& rhs); // == operator overload

	// sphere functions
	static Matrix normalAt(Sphere s, const Matrix& world_point); // returns a Vector, takes a Point
};

#endif

