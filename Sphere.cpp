// Matthew Kerr

#include "Sphere.h"
#include "Matrix.h"

Sphere::Sphere()
{
	this->radii = 0.0;
	Matrix temp;
	temp.identity(4);
	this->transformation = temp;
}

Sphere::~Sphere() { }

Sphere::Sphere(const double& radii)
{
	this->radii = radii;
	Matrix temp;
	temp.identity(4);
	this->transformation = temp;
}

void Sphere::setTransforms(Matrix m)
{
	this->transformation = m;
}