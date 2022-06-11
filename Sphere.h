// Matthew Kerr

#ifndef SPHERE_H
#define SPHERE_H

#include "Matrix.h"
using namespace std;

class Sphere
{
public:
	double radii;
	Matrix transformation;

	// constructors
	Sphere();
	virtual ~Sphere();
	Sphere(const double& radii);

	// sphere functions
	void setTransforms(Matrix m);
};

#endif

