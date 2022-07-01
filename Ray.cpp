// Matthew Kerr

#include "Ray.h"

Ray::Ray() { }

Ray::~Ray() { }

Ray::Ray(Matrix origin, Matrix direction)
{
	this->origin = origin;
	this->direction = direction;
}