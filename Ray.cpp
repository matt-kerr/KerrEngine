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

Matrix Ray::position(const Ray& r, const double& t)
{
	return r.origin + (r.direction * t);
}


std::vector<Intersection> Ray::intersectSphere(const Ray& r, Sphere* s)
{
	std::vector<Intersection> ret;
	double a, b, c, discriminant;
	Ray ray2 = Ray::transform(r, Matrix::inverse((*s).transform));
	Matrix sphere_to_ray = ray2.origin - Matrix::point(0.0, 0.0, 0.0);
	a = Matrix::dot(ray2.direction, ray2.direction);
	b = 2.0 * Matrix::dot(ray2.direction, sphere_to_ray);
	c = Matrix::dot(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2.0) - (4.0 * a * c);
	if (discriminant < 0)
	{
		return ret;
	}
	ret.push_back(Intersection(((-b - sqrt(discriminant)) / (a * 2.0)), s, "SPHERE"));
	ret.push_back(Intersection(((-b + sqrt(discriminant)) / (a * 2.0)), s, "SPHERE"));

	return ret;
}

Ray Ray::transform(const Ray& r, const Matrix& m)
{
	Ray result(m * r.origin, m * r.direction);
	return result;
}