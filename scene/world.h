// Matthew Kerr

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <iostream>
#include "../primitives/color.h"
#include "../primitives/transformation.h"
#include "../primitives/ray.h"
#include "../primitives/intersection.h"
#include "../primitives/intersections.h"
#include "../lights/light.h"
#include "../lights/point_light.h"
#include "../scene/prepared_computation.h"
#include "../shapes/material.h"
#include "../shapes/shape.h"
#include "../shapes/sphere.h"
#include "../shapes/plane.h"
#include "../patterns/pattern.h"

class Color;
class Light;
class PointLight;
class Ray;
class intersection;
class intersections;
class PreparedComputation;
class Material;
class Shape;
class Sphere;
class Plane;
class Pattern;
class World
{
	public:
		Light *_light = nullptr;
		std::vector<Shape *> _shapes;

		World();
		virtual ~World() = default;

		void add_shape(Shape *obj);
		void clear();	
};

World default_world();
Intersections intersect_world(const World &world, const Ray& r);
bool is_shadowed(const World &w, const Tuple &point);
Color shade_hit(World w, PreparedComputation comps, int remaining);
Color color_at(World w, Ray r, int remaining);
Color lighting(const Material &material, Shape *object, Light *light, const Tuple &point, const Tuple &eyev, const Tuple &normalv, const bool &in_shadow);
Color pattern_at_object(Pattern *pattern, Shape *object, Tuple world_point);
Color reflected_color(World world, PreparedComputation comps, int remaining);
Color refracted_color(World world, PreparedComputation comps, int remaining);
double schlick(PreparedComputation comps);


#endif;