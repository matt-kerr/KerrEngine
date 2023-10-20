// Matthew Kerr

#include "sphere.h"

Sphere::Sphere() : Shape() { }

const Intersections Sphere::local_intersect(Ray ray) const {
	Intersections ret;
	double a, b, c, discriminant;
	Tuple sphere_to_ray = ray._origin - create_point(0.0, 0.0, 0.0);
	a = dot(ray._direction, ray._direction);
	b = 2.0 * dot(ray._direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - 1.0;
	discriminant = std::pow(b, 2.0) - 4.0 * a * c;
	if (discriminant < 0.0) { return ret; }
	double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
	double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);
	ret.merge(Intersection(t1, (void *)this));
	ret.merge(Intersection(t2, (void *)this));
	return ret;
}

const Tuple Sphere::local_normal_at(Tuple local_point) const {
	return local_point - create_point(0.0, 0.0, 0.0);
}

const BoundingBox Sphere::bounds() const {
	return BoundingBox(create_point(-1.0, -1.0, -1.0), create_point(1.0, 1.0, 1.0));
}

void Sphere::divide(const int &threshold) { return; }

void Sphere::delete_children() { return; }