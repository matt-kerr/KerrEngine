// Matthew Kerr

#include "Cylinder.h"

Cylinder::Cylinder() : Shape() {
	_min = -BIG_NUM;
	_max = BIG_NUM;
	_closed = false;
}

Cylinder::Cylinder(const double& min, const double& max, const bool& closed)
{
	_min = min;
	_max = max;
	_closed = closed;
}

const Intersections Cylinder::local_intersect(Ray ray) const {
	Intersections xs;
	double a = std::pow(ray._direction._x, 2) + std::pow(ray._direction._z, 2);
	if (!(std::abs(a) < EPSILON)) {
		double b = 2.0 * ray._origin._x * ray._direction._x + 2.0 * ray._origin._z * ray._direction._z;
		double c = std::pow(ray._origin._x, 2) + std::pow(ray._origin._z, 2) - 1.0;
		double disc = std::pow(b, 2) - 4.0 * a * c;
		if (disc < 0.0) { return xs; }
		double t0 = (-b - std::sqrt(disc)) / (2.0 * a);
		double t1 = (-b + std::sqrt(disc)) / (2.0 * a);
		if (t0 > t1) { std::swap(t0, t1); }
		double y0 = ray._origin._y + t0 * ray._direction._y;
		if (_min < y0 && y0 < _max) { xs.merge(Intersection(t0, (void *)this)); }
		double y1 = ray._origin._y + t1 * ray._direction._y;
		if (_min < y1 && y1 < _max) { xs.merge(Intersection(t1, (void *)this)); }
	}
	xs.merge(intersect_caps(ray));
	return xs;
}

const Tuple Cylinder::local_normal_at(Tuple point) const
{
	double dist = std::pow(point._x, 2) + std::pow(point._z, 2);
	if (dist < 1.0 && point._y >= _max - EPSILON) { return create_vector(0.0, 1.0, 0.0); }
	if (dist < 1.0 && point._y <= _min + EPSILON) { return create_vector(0.0, -1.0, 0.0); }
	return create_vector(point._x, 0.0, point._z);
}

const BoundingBox Cylinder::bounds() const {

	double ymin = (_min != -BIG_NUM) ? _min : -BIG_NUM;
	double ymax = (_max != BIG_NUM) ? _max : BIG_NUM;
	return BoundingBox(create_point(-1.0, ymin, -1.0), create_point(1.0, ymax, 1.0));
}

void Cylinder::divide(const int &threshold) { return; }

void Cylinder::delete_children() { return; }

const Intersections Cylinder::intersect_caps(Ray ray) const
{
	Intersections xs;
	if (!_closed || std::abs(ray._direction._y) < EPSILON) { return xs; }
	double t = (_min - ray._origin._y) / ray._direction._y;
	if (check_cap(ray, t)) { xs.merge(Intersection(t, (void *)this)); }
	t = (_max - ray._origin._y) / ray._direction._y;
	if (check_cap(ray, t)) { xs.merge(Intersection(t, (void *)this)); }
	return xs;
}

const bool check_cap(Ray ray, double t)
{
	double x = ray._origin._x + t * ray._direction._x;
	double z = ray._origin._z + t * ray._direction._z;
	return (std::pow(x, 2) + std::pow(z, 2)) <= 1.0;
}

