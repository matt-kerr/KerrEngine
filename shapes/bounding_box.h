// Matthew Kerr

#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <iostream>

#include "../kerr_inline.h"
#include "../kerr_math.h"
#include "../primitives/tuple.h"
#include "../primitives/matrix.h"
#include "../primitives/ray.h"


class Tuple;
class Matrix;
class Ray;
class BoundingBox {
    friend std::ostream& operator<<(std::ostream &out, const BoundingBox &b);

    public:
        Tuple _min;
        Tuple _max;

        BoundingBox();
        virtual ~BoundingBox() = default;     
        BoundingBox(Tuple min, Tuple max);

        void add_point(Tuple point);
        void add_box(BoundingBox box);
        bool contains_point(Tuple point);
        bool contains_box(BoundingBox box);
        bool intersects(Ray ray) const;
        BoundingBox transform(Matrix transform);
        std::vector<BoundingBox> split_bounds();
};

#endif