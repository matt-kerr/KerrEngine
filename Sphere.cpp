// Matthew Kerr

#include "Sphere.h"
#include "Matrix.h"
#include "KerrEngineException.h"

Sphere::Sphere()
{
	this->radii = 0.0;
	Matrix temp;
	temp.identity(4);
	this->transform = temp;
}

Sphere::~Sphere() { }

Sphere::Sphere(const double& radii)
{
	this->radii = radii;
	this->transform.identity(4);
}

Sphere::Sphere(const double& radii, Matrix transform, Material material)
{
	this->radii = radii;
	this->transform = transform;
	this->material = material;
}

void Sphere::setTransforms(Matrix m)
{
	this->transform = m;
}

Matrix Sphere::normalAt(Matrix world_point)
{
	//cout << "entered Sphere::normalAt" << endl;
	if (world_point.rows != 4 || world_point.cols != 1 || world_point(3, 0) != 1) { throw KerrEngineException(EXCEPTION_NORMAL_AT_SPHERE_INVALID_MATRIX_SIZE); }
	Matrix center;
	center.point(0.0, 0.0, 0.0);
	//cout << "this->transform:" << endl << this->transform << endl << endl;
	//cout << "this->transform.inverse():" << endl << this->transform.inverse() << endl << endl;
	Matrix object_point = this->transform.inverse() * world_point;
	Matrix object_normal = object_point - center;
	Matrix world_normal = (this->transform.inverse()).transpose() * object_normal;
	world_normal(3, 0) = 0.0;
	return world_normal.normalize();
}

/*
Matrix Sphere::normalAt(Matrix p)
{
	if (p.rows != 4 || p.cols != 1 || p(3, 0) != 1) { throw KerrEngineException(EXCEPTION_NORMAL_AT_SPHERE_INVALID_MATRIX_SIZE); }
	Matrix center, temp;
	center.point(0.0, 0.0, 0.0);
	temp = p - center;
	//cout << temp << endl;
	//cout << temp.normalize() << endl;
	return temp.normalize();
}
*/