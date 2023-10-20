// Matthew Kerr

#ifndef SHAPE_H
#define SHAPE_H

#include "../kerr_inline.h"
#include "../primitives/tuple.h"
#include "../primitives/intersections.h"
#include "../primitives/ray.h"
#include "material.h"
#include "bounding_box.h"

class Tuple;
class Intersections;
class Ray;
class Material;
class BoundingBox;
class Shape
{
    friend std::ostream& operator<<(std::ostream &out, const Shape &s);

    public:
        Matrix _transform = identity_matrix(4);
        Material _material;
        Shape *_parent = nullptr;

        Shape();
        virtual ~Shape() = default;

        Intersections intersect(Ray ray);
        Tuple normal_at(Tuple world_point);
        BoundingBox parent_space_bounds();

        virtual const Intersections local_intersect(Ray ray) const = 0;
        virtual const Tuple local_normal_at(Tuple local_point) const = 0;   
        virtual const BoundingBox bounds() const = 0;
        virtual void divide(const int &threshold) = 0;
        virtual void delete_children() = 0;
};

Tuple world_to_object(Shape *shape, Tuple point);
Tuple normal_to_world(Shape *shape, Tuple normal);

#endif