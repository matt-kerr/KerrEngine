// Matthew Kerr

#include <string>
#include "Computations.h"
#include "KerrEngineException.h"

Computations::Computations() { throw KerrEngineException("Default constructor for Computations should not be used."); }

Computations::~Computations() { }

Computations::Computations(double t, Sphere obj, Matrix point, Matrix eyev, Matrix normalv, bool inside)
{
	this->t = t;
	this->obj = obj;
	this->point = point;
	this->eyev = eyev;
	this->normalv = normalv;
	this->inside = inside;
}

Computations::Computations(const Computations& orig)
{
	this->t = orig.t;
	this->obj = orig.obj;
	this->point = orig.point;
	this->eyev = orig.eyev;
	this->normalv = orig.normalv;
}
Computations::Computations(Computations&& orig)
{
	this->t = orig.t;
	this->obj = orig.obj;
	this->point = orig.point;
	this->eyev = orig.eyev;
	this->normalv = orig.normalv;
}

Computations& Computations::operator=(const Computations& rhs)
{
	this->t = rhs.t;
	this->obj = rhs.obj;
	this->point = rhs.point;
	this->eyev = rhs.eyev;
	this->normalv = rhs.normalv;
	return *this;
}

Computations& Computations::operator=(Computations&& orig)
{
	this->t = orig.t;
	this->obj = orig.obj;
	this->point = orig.point;
	this->eyev = orig.eyev;
	this->normalv = orig.normalv;
	return *this;
}

Computations Computations::prepareComputations(Intersection intersection, Ray ray)
{
	double t = intersection.t;
	Sphere obj = intersection.obj;
	Matrix point = Ray::position(ray, t);
	Matrix eyev = -ray.direction;
	Matrix normalv;
	bool inside = false;

	normalv = Sphere::normalAt(obj, point);
	if (Matrix::dot(normalv, eyev) < 0.0)
	{
		inside = true;
		normalv = -normalv;
	}
	else
	{
		inside = false;
	}

	return Computations(t, obj, point, eyev, normalv, inside);
}