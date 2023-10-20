// Matthew Kerr

#include "plane.h"

Plane::Plane() : Shape() { }

const Intersections Plane::local_intersect(Ray ray) const {
	Intersections xs;
	if (std::abs(ray._direction._y) < EPSILON) { return xs; }
	xs.merge(Intersection(-ray._origin._y / ray._direction._y, (void *)this));
	return xs;
}

const Tuple Plane::local_normal_at(Tuple point) const {
	return create_vector(0.0, 1.0, 0.0);
}

const BoundingBox Plane::bounds() const {
	return BoundingBox(create_point(-BIG_NUM, 0.0, -BIG_NUM), create_point(BIG_NUM, 0.0, BIG_NUM));
}

void Plane::divide(const int &threshold) { return; }

void Plane::delete_children() { return; }