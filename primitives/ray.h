// Matthew Kerr

#ifndef RAY_H
#define RAY_H

#include <iostream>
#include "matrix.h"
#include "tuple.h"

class Matrix;
class Tuple;
class Ray
{
    friend std::ostream& operator<<(std::ostream &out, const Ray &r);

    public:
        Tuple _origin;
        Tuple _direction;

        Ray() { throw std::invalid_argument("Ray requires origin/direction arguments"); }
        Ray(const Tuple &origin, const Tuple &direction);
        virtual ~Ray() = default; 
};

Ray transform_ray(const Ray &r, const Matrix &m);
Tuple position(const Ray &r, const double &t);

#endif