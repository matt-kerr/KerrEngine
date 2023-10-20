// Matthew Kerr

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include "../kerr_inline.h"

class Intersection
{
    public:
        friend std::ostream& operator<<(std::ostream &out, const Intersection &i);

        double _t;
        void *_obj = nullptr;

        Intersection();
        Intersection(const double &t, void *obj);
        virtual ~Intersection() = default;        
};

bool operator==(const Intersection &lhs, const Intersection &rhs);

#endif