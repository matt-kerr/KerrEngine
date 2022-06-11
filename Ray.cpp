// Matthew Kerr

#include "Ray.h"
#include "Matrix.h"
#include "Sphere.h"
#include "Intersection.h"
#include "KerrEngineException.h"

Ray::Ray()
{

}

Ray::~Ray() { }

Ray::Ray(Matrix origin, Matrix direction)
{
	this->origin = origin;
	this->direction = direction;
}

Matrix Ray::position(const double& t)
{
	return this->origin + (this->direction * t);
}

Intersection* Ray::intersectSphere(Sphere *s)
{
	Matrix s_transform_inverse = (*s).transformation;
	s_transform_inverse.inverse();
	Ray ray2 = this->transform(s_transform_inverse);
	Intersection* ret = new Intersection[2];
	double a, b, c, discriminant;
	Matrix center, sphere_to_ray;

	center.point(0.0, 0.0, 0.0);
	sphere_to_ray = ray2.origin - center;
	a = ray2.direction.dotProductVector(ray2.direction);
	b = 2.0 * ray2.direction.dotProductVector(sphere_to_ray);
	c = sphere_to_ray.dotProductVector(sphere_to_ray) - pow((*s).radii, 2);
	discriminant = pow(b, 2) - (4.0 * a * c);
	if (discriminant < 0.0)
	{
		Intersection* ret = new Intersection[2];
		ret[0].t = -1.00;
		ret[0].obj = NULL;
		ret[0].obj_type = "NONE";
		ret[1].t = -1.00;
		ret[1].obj = NULL;
		ret[1].obj_type = "NONE";
	}
	else
	{
		ret[0].t = ((b * -1.0) - sqrt(discriminant)) / (2 * a);
		ret[0].obj = NULL;
		ret[0].obj_type = "SPHERE";
		ret[1].t = ((b * -1.0) + sqrt(discriminant)) / (2 * a);
		ret[1].obj = NULL;
		ret[1].obj_type = "SPHERE";
	}

	return ret;
}

Ray Ray::transform(Matrix m)
{
	Ray result(m * this->origin,m * this->direction);
	return result;
}