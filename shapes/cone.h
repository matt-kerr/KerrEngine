// Matthew Kerr


#ifndef CONE_H
#define CONE_H

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
class Cone : public Shape
{
	public:
		double _min;
		double _max;
		bool _closed;

		Cone();
		Cone(const double& min, const double& max, const bool& closed);
		virtual ~Cone() = default;

		const Intersections local_intersect(Ray ray) const;
		const Tuple local_normal_at(Tuple point) const;
		const BoundingBox bounds() const;
		const Intersections intersect_caps(Ray ray) const;
		void divide(const int &threshold);
		void delete_children();
};

const bool check_cap(Ray ray, double t, double y);

#endif


