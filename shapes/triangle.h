// Matthew Kerr


#ifndef TRIANGLE_H
#define TRIANGLE_H

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
class Triangle : public Shape {
	public:
		Tuple _p1;
		Tuple _p2;
		Tuple _p3;
		Tuple _e1;
		Tuple _e2;
		Tuple _normal;

		Triangle() { throw std::invalid_argument("Triangle requires (point, point, point) arguments"); };
		virtual ~Triangle() = default;
		Triangle(const Tuple &p1, const Tuple &p2, const Tuple p3);

		const Intersections local_intersect(Ray ray) const;
		const Tuple local_normal_at(Tuple point) const;
		const BoundingBox bounds() const;
		void divide(const int &threshold);
		void delete_children();
};

#endif


