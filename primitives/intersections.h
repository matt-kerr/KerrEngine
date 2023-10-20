// Matthew Kerr

#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include <iostream>
#include <vector>

#include "intersection.h"

class Intersection;
class Intersections
{
    public:
        std::vector<Intersection> _intersections;

        Intersections();
        Intersections(std::vector<Intersection> intersections);
        virtual ~Intersections() = default;

        Intersection operator[](const int &index);

        inline int count() const { return (int)_intersections.size(); }

        void merge(Intersection other);
        void merge(Intersections other);
};

Intersection hit(Intersections xs);

#endif