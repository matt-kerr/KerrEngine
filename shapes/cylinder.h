// Matthew Kerr


#ifndef CYLINDER_H
#define CYLINDER_H

#include <iostream>
#include <vector>

#include "shape.h"
#include "../primitives/intersections.h"
#include "../primitives/ray.h"
#include "../primitives/tuple.h"

class Intersections;
class Ray;
class Shape;
class Tuple;
class Cylinder : public Shape
{
	public:
		double _min;
		double _max;
		bool _closed;

		Cylinder();
		Cylinder(const double& minimum, const double& maximum, const bool& closed);
		virtual ~Cylinder() = default;

		const Intersections local_intersect(Ray ray) const;
		const Tuple local_normal_at(Tuple point) const;
		const BoundingBox bounds() const;
		void divide(const int &threshold);
		void delete_children();

		const Intersections intersect_caps(Ray ray) const;
};

const bool check_cap(Ray ray, double t);

#endif


