// Matthew Kerr


#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <vector>


#include "../primitives/intersections.h"
#include "../primitives/ray.h"
#include "../primitives/tuple.h"
#include "shape.h"
#include "bounding_box.h"

class Intersections;
class Ray;
class Tuple;
class Shape;
class BoundingBox;
class Sphere : public Shape
{
	public:
		Sphere();
		virtual ~Sphere() = default;

		const Intersections local_intersect(Ray ray) const;
		const Tuple local_normal_at(Tuple point) const;
		const BoundingBox bounds() const;
		void divide(const int &threshold);
		void delete_children();
};

#endif


