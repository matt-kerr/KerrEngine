// Matthew Kerr

#include "Sphere.h"

Sphere::Sphere() { this->transform = Matrix::identity(4); }

Sphere::~Sphere() { }

// copy constructor
Sphere::Sphere(const Sphere& orig)
{
	this->transform = orig.transform;
	this->material = orig.material;
}

// move constructor
Sphere::Sphere(Sphere&& orig) noexcept
{
	this->transform = orig.transform;
	this->material = orig.material;
}

// = operator overload
Sphere& Sphere::operator=(const Sphere& rhs)
{
	this->transform = rhs.transform;
	this->material = rhs.material;
	return *this;
}

// move = operator overload (move assignment overload)
Sphere& Sphere::operator=(Sphere&& orig)
{
	if (this != &orig)
	{
		this->transform = orig.transform;
		this->material = orig.material;
	}
	return *this;
}

// == operator overload
bool Sphere::operator==(const Sphere& rhs)
{
	return (this->material == rhs.material) && (this->transform == rhs.transform);
}

Matrix Sphere::normalAt(Sphere s, const Matrix& world_point)
{
	if (world_point.rows != 4 || world_point.cols != 1 || world_point(3, 0) != 1) { throw KerrEngineException("EXCEPTION_NORMAL_AT_SPHERE_INVALID_MATRIX_SIZE"); }
	Matrix object_point = Matrix::inverse(s.transform) * world_point;
	Matrix object_normal = object_point - Matrix::point(0.0, 0.0, 0.0);
	Matrix world_normal = Matrix::transpose(Matrix::inverse(s.transform)) * object_normal;
	world_normal(3, 0) = 0.0;
	return Matrix::normalize(world_normal);
}