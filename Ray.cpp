// Matthew Kerr

#include "Ray.h"
#include "KerrEngine.h"
#include "KerrEngineException.h"
#include "Matrix.h"
#include "Sphere.h"
#include "Intersection.h"

Ray::Ray() { }

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


std::vector<Intersection> Ray::intersectSphere(const Ray& r, Sphere s)
{
	if (DEBUG) { cout << "        Ray::intersectSphere entered" << endl; }
	std::vector<Intersection> ret;
	double a, b, c, discriminant;
	Ray ray2 = Ray::transform(r, Matrix::inverse(s.transform));
	Matrix sphere_to_ray = ray2.origin - Matrix::point(0.0, 0.0, 0.0);
	a = Matrix::dot(ray2.direction, ray2.direction);
	b = 2.0 * Matrix::dot(ray2.direction, sphere_to_ray);
	c = Matrix::dot(sphere_to_ray, sphere_to_ray) - 1;
	a = (std::abs(a) < EPSILON) ? 0.0 : a;
	b = (std::abs(b) < EPSILON) ? 0.0 : b;
	c = (std::abs(c) < EPSILON) ? 0.0 : c;
	discriminant = pow(b, 2.0) - (4.0 * a * c);
	discriminant = (std::abs(discriminant) < EPSILON) ? 0.0 : discriminant;
	if (discriminant < 0)
	{
		if (DEBUG) { cout << "        Ray::intersectSphere discriminant = " << discriminant << ", returning early" << endl; }
		return ret;
	}

	double t1 = ((-b - sqrt(discriminant)) / (a * 2.0));
	double t2 = ((-b + sqrt(discriminant)) / (a * 2.0));
	if (std::abs(t1) < EPSILON) { t1 = 0.0; }
	if (std::abs(t2) < EPSILON) { t2 = 0.0; }

	if (DEBUG)
	{
		cout << "        Ray::intersectSphere a = " << a << endl;
		cout << "        Ray::intersectSphere b = " << b << endl;
		cout << "        Ray::intersectSphere c = " << c << endl;
		cout << "        Ray::intersectSphere discriminant = " << discriminant << endl;
		cout << "        Ray::intersectSphere t1 = " << t1 << endl;
		cout << "        Ray::intersectSphere t2 = " << t2 << endl;
		cout << "        Ray::intersectSphere exiting" << endl;
	}
	ret.push_back(Intersection(t1, s));
	ret.push_back(Intersection(t2, s));
	return ret;
}

Ray Ray::transform(const Ray& r, const Matrix& m)
{
	Ray result((m * r.origin), (m * r.direction));
	return result;
}