// Matthew Kerr

#include "triangle.h"

Triangle::Triangle(const Tuple &p1, const Tuple &p2, const Tuple p3) : Shape() {
	_p1 = p1;
	_p2 = p2;
	_p3 = p3;
	_e1 = p2 - p1;
	_e2 = p3 - p1;
	_normal = normalize(cross(_e2,_e1));
}

const Intersections Triangle::local_intersect(Ray ray) const {
	Intersections ret;
	Tuple dir_cross_e2 = cross(ray._direction, _e2);
	double det = dot(_e1, dir_cross_e2);
	if (abs(det) < EPSILON) { return ret; }

	double f = 1.0 / det;
	Tuple p1_to_origin = ray._origin - _p1;
	double u = f * dot(p1_to_origin, dir_cross_e2);
	if (u < 0.0 || u > 1.0) { return ret; }

	Tuple origin_cross_e1 = cross(p1_to_origin, _e1);
	double v = f * dot(ray._direction, origin_cross_e1);
	if (v < 0.0 || (u + v) > 1.0) { return ret; }

	double t = f * dot(_e2, origin_cross_e1);
	ret.merge(Intersection(t, (Shape *)this));
	return ret;
}

const Tuple Triangle::local_normal_at(Tuple local_point) const {
	return _normal;
}

const BoundingBox Triangle::bounds() const {
	double minx = std::min(_p1._x, std::min(_p2._x, _p3._x));
	double miny = std::min(_p1._y, std::min(_p2._y, _p3._y));
	double minz = std::min(_p1._z, std::min(_p2._z, _p3._z));
	double maxx = std::max(_p1._x, std::max(_p2._x, _p3._x));
	double maxy = std::max(_p1._y, std::max(_p2._y, _p3._y));
	double maxz = std::max(_p1._z, std::max(_p2._z, _p3._z));
	return BoundingBox(create_point(minx, miny, minz), create_point(maxx, maxy, maxz));
}

void Triangle::divide(const int &threshold) { return; }

void Triangle::delete_children() { return; }