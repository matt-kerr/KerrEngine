// Matthew Kerr

#include "Computations.h"

Computations::Computations() { throw KerrEngineException("Default constructor for Computations should not be used."); }

Computations::~Computations() { }

Computations::Computations(double t, Shape* obj, Matrix point, Matrix over_point, Matrix eyev, Matrix normalv, Matrix reflectv, bool inside, double n1, double n2)
{
	this->t = t;
	this->obj = obj;
	this->point = point;
	this->over_point = over_point;
	this->eyev = eyev;
	this->normalv = normalv;
	this->reflectv = reflectv;
	this->inside = inside;
	this->n1 = n1;
	this->n2 = n2;
}

Computations::Computations(const Computations& orig)
{
	this->t = orig.t;
	this->obj = orig.obj;
	this->point = orig.point;
	this->over_point = orig.over_point;
	this->eyev = orig.eyev;
	this->normalv = orig.normalv;
	this->reflectv = orig.reflectv;
	this->n1 = orig.n1;
	this->n2 = orig.n2;
}
Computations::Computations(Computations&& orig)
{
	this->t = orig.t;
	this->obj = orig.obj;
	this->point = orig.point;
	this->over_point = orig.over_point;
	this->eyev = orig.eyev;
	this->normalv = orig.normalv;
	this->reflectv = orig.reflectv;
	this->n1 = orig.n1;
	this->n2 = orig.n2;
}

Computations& Computations::operator=(const Computations& rhs)
{
	this->t = rhs.t;
	this->obj = rhs.obj;
	this->point = rhs.point;
	this->over_point = rhs.over_point;
	this->eyev = rhs.eyev;
	this->normalv = rhs.normalv;
	this->reflectv = rhs.reflectv;
	this->n1 = rhs.n1;
	this->n2 = rhs.n2;
	return *this;
}

Computations& Computations::operator=(Computations&& orig)
{
	this->t = orig.t;
	this->obj = orig.obj;
	this->point = orig.point;
	this->over_point = orig.over_point;
	this->eyev = orig.eyev;
	this->normalv = orig.normalv;
	this->reflectv = orig.reflectv;
	this->n1 = orig.n1;
	this->n2 = orig.n2;
	return *this;
}