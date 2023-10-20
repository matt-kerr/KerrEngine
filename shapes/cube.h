// Matthew Kerr


#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <vector>

#include "../kerr_math.h"
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
class Cube : public Shape
{
	public:
		Cube();
		virtual ~Cube() = default;

		const Intersections local_intersect(Ray ray) const;
		const Tuple local_normal_at(Tuple point) const;
		const BoundingBox bounds() const;
		void divide(const int &threshold);
		void delete_children();
};

#endif


