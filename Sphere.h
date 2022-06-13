// Matthew Kerr

#ifndef SPHERE_H
#define SPHERE_H

#include "Matrix.h"
#include "Material.h"
using namespace std;

class Sphere
{
public:
	double radii;
	Matrix transform;
	Material material;

	// constructors
	Sphere();
	virtual ~Sphere();
	Sphere(const double& radii);
	Sphere(const double& radii, Matrix transform, Material material);

	// sphere functions
	void setTransforms(Matrix m);
	Matrix normalAt(Matrix world_point); // returns a Vector, takes a Point
};

#endif

