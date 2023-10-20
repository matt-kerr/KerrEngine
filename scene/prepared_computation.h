// Matthew Kerr

#ifndef PREPAREDCOMPUTATION_H
#define PREPAREDCOMPUTATION_H

#include <algorithm>
#include <iostream>
#include "../kerr_inline.h"
#include "../primitives/intersection.h"
#include "../primitives/ray.h"
#include "../primitives/tuple.h"
#include "../shapes/shape.h"

class Intersection;
class Ray;
class Tuple;
class Shape;
class PreparedComputation
{
	friend std::ostream& operator<<(std::ostream &out, const PreparedComputation &comps);

	public:
		double _t;
		Shape *_obj;
		Tuple _point;
		Tuple _over_point;
		Tuple _under_point;
		Tuple _eyev;
		Tuple _normalv;
		Tuple _reflectv;
		bool _inside;
		double _n1;
		double _n2;

		PreparedComputation() { throw std::invalid_argument("PreparedComputation requires arguments"); }
		PreparedComputation(Intersection hit, Ray ray, Intersections xs);
		virtual ~PreparedComputation() = default;
};

#endif