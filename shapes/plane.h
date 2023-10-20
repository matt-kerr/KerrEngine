// Matthew Kerr

#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <vector>

#include "../primitives/intersection.h"
#include "../primitives/intersections.h"
#include "../primitives/ray.h"
#include "../primitives/tuple.h"
#include "shape.h"
#include "bounding_box.h"

class Intersection;
class Intersections;
class Ray;
class Tuple;
class Shape;
class BoundingBox;
class Plane : public Shape
{
	public:
		Plane();
		virtual ~Plane() = default;

		const Intersections local_intersect(Ray ray) const;
		const Tuple local_normal_at(Tuple point) const;
		const BoundingBox bounds() const;
		void divide(const int &threshold);
		void delete_children();
};

#endif

