// Matthew Kerr


#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <vector>
#include <string>

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
class Group : public Shape
{
	public:
		std::vector<Shape *> _shapes;
		BoundingBox _bounds;
		std::string _name;

		Group();
		virtual ~Group() = default;

		void add_child(Shape *s);
		std::vector<std::vector<Shape *>> partition_children();
		void make_subgroup(std::vector<Shape *> shapes);

		const Intersections local_intersect(Ray ray) const;
		const Tuple local_normal_at(Tuple point) const;
		const BoundingBox bounds() const;
		void divide(const int &threshold);
		void delete_children();
};

#endif


