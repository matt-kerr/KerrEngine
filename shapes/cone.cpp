// Matthew Kerr

#include "Cone.h"

Cone::Cone() : Shape() {
	_min = -BIG_NUM;
	_max = BIG_NUM;
	_closed = false;
}

Cone::Cone(const double& min, const double& max, const bool& closed) {
	_min = min;
	_max = max;
	_closed = closed;
}

const Intersections Cone::local_intersect(Ray ray) const {
	Intersections xs;
	double a = std::pow(ray._direction._x, 2.0) - std::pow(ray._direction._y, 2.0) + std::pow(ray._direction._z, 2.0);
	double b = (2.0 * ray._origin._x * ray._direction._x) - (2.0 * ray._origin._y * ray._direction._y) + (2.0 * ray._origin._z * ray._direction._z);
	double c = std::pow(ray._origin._x, 2.0) - std::pow(ray._origin._y, 2.0) + std::pow(ray._origin._z, 2.0);
	if (std::abs(a) < EPSILON && std::abs(b) > EPSILON) {
			double t = -c / (2.0 * b);
			xs.merge(Intersection(t, (void *)this));
			xs.merge(intersect_caps(ray));
			return xs;
	}
	double disc = std::pow(b, 2.0) - 4.0 * a * c;
	if (std::abs(disc) < EPSILON) { disc = 0.0; }
	if (disc < 0.0) { return xs; }
	double t0 = (-b - std::sqrt(disc)) / (2.0 * a);
	double t1 = (-b + std::sqrt(disc)) / (2.0 * a);
	if (t0 > t1) { std::swap(t0, t1); }
	double y0 = ray._origin._y + t0 * ray._direction._y;
	double y1 = ray._origin._y + t1 * ray._direction._y;
	if (_min < y0 && y0 < _max) { xs.merge(Intersection(t0, (void *)this)); }
	if (_min < y1 && y1 < _max) { xs.merge(Intersection(t1, (void *)this)); }

	xs.merge(intersect_caps(ray));
	return xs;
}

const Tuple Cone::local_normal_at(Tuple point) const {
	double dist = std::pow(point._x, 2.0) + std::pow(point._z, 2.0);
	if (dist < 1.0 && point._y >= _max - EPSILON) { return create_vector(0.0, 1.0, 0.0); }
	if (dist < 1.0 && point._y <= _min + EPSILON) { return create_vector(0.0, -1.0, 0.0); }
	double y = sqrt(std::pow(point._x, 2.0) + std::pow(point._z, 2.0));
	if (point._y > 0.0) { y = -y; }
	return create_vector(point._x, y, point._z);
}

const BoundingBox Cone::bounds() const {
	double a = std::abs(_min);
	double b = std::abs(_max);
	double limit = std::max(a, b);
	return BoundingBox(create_point(-limit, _min, -limit), create_point(limit, _max, limit));
}

const Intersections Cone::intersect_caps(Ray ray) const {
	Intersections xs;
	if (!_closed || std::abs(ray._direction._y) < EPSILON) { return xs; }
	double t = (_min - ray._origin._y) / ray._direction._y;
	if (check_cap(ray, t, std::abs(_min))) { xs.merge(Intersection(t, (void *)this)); }
	t = (_max - ray._origin._y) / ray._direction._y;
	if (check_cap(ray, t, std::abs(_max))) { xs.merge(Intersection(t, (void *)this)); }
	return xs;
}

void Cone::divide(const int &threshold) { return; }

void Cone::delete_children() { return; }

const bool check_cap(Ray ray, double t, double y) {
	double x = ray._origin._x + t * ray._direction._x;
	double z = ray._origin._z + t * ray._direction._z;
	return (std::pow(x, 2.0) + std::pow(z, 2.0)) <= y;
}

