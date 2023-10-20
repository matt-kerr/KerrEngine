// Matthew Kerr


#ifndef GLASS_SPHERE_H
#define GLASS_SPHERE_H

#include <iostream>
#include <vector>

#include "shape.h"
#include "sphere.h"
#include "../primitives/intersections.h"
#include "../primitives/ray.h"
#include "../primitives/tuple.h"

class Intersections;
class Ray;
class Tuple;
class Shape;
class Sphere;
class GlassSphere : public Sphere
{
	public:
		GlassSphere();
		virtual ~GlassSphere() = default;
};

#endif


