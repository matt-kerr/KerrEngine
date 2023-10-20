// Matthew Kerr

#include "cube.h"

Cube::Cube() : Shape() { }

const Intersections Cube::local_intersect(Ray ray) const {
	Intersections ret;
	std::vector<double> xt = check_axis(ray._origin._x, ray._direction._x, -1.0, 1.0);
	std::vector<double> yt = check_axis(ray._origin._y, ray._direction._y, -1.0, 1.0);
	std::vector<double> zt = check_axis(ray._origin._z, ray._direction._z, -1.0, 1.0);
	double tmin = std::max(xt[0], std::max(yt[0], zt[0]));
	double tmax = std::min(xt[1], std::min(yt[1], zt[1]));
	if (tmin > tmax) { return ret; }
	ret.merge(Intersection(tmin, (void *)this));
	ret.merge(Intersection(tmax, (void *)this));
	return ret;
}

const Tuple Cube::local_normal_at(Tuple local_point) const {
	double maxc = std::max(std::abs(local_point._x), std::max(std::abs(local_point._y), std::abs(local_point._z)));
	if (maxc == std::abs(local_point._x)) { return create_vector(local_point._x, 0.0, 0.0); }
	else if (maxc == std::abs(local_point._y)) { return create_vector(0.0, local_point._y, 0.0); }
	 return create_vector(0.0, 0.0, local_point._z);
}

const BoundingBox Cube::bounds() const {
	return BoundingBox(create_point(-1.0, -1.0, -1.0), create_point(1.0, 1.0, 1.0));
}

void Cube::divide(const int &threshold) { return; }

void Cube::delete_children() { return; }