// Matthew Kerr

#include "Ray.h"

Ray::Ray() { }

Ray::~Ray() { }

Ray::Ray(Matrix origin, Matrix direction)
{
	this->origin = origin;
	this->direction = direction;
}

Matrix Ray::position(const Ray& r, const double& t)
{
	return r.origin + r.direction * t;
}


std::vector<Intersection> Ray::intersectSphere(const Ray& r, Sphere s)
{
	std::vector<Intersection> ret;
	double a, b, c, discriminant;
	Ray ray2 = Ray::transform(r, Matrix::inverse(s.transform));
	Matrix sphere_to_ray = ray2.origin - Matrix::point(0.0, 0.0, 0.0);
	a = Matrix::dot(ray2.direction, ray2.direction);
	b = 2.0 * Matrix::dot(ray2.direction, sphere_to_ray);
	c = Matrix::dot(sphere_to_ray, sphere_to_ray) - 1.0;
	discriminant = pow(b, 2.0) - 4.0 * a * c;
	if (discriminant < 0.0) { return ret; }
	double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	ret.push_back(Intersection(t1, s));
	ret.push_back(Intersection(t2, s));
	return ret;
}

Ray Ray::transform(const Ray& r, const Matrix& m)
{
	Ray result((m * r.origin), (m * r.direction));
	return result;
}