// Matthew Kerr

#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>
#include "../kerr_inline.h"

class Tuple
{
    friend std::ostream& operator<<(std::ostream &out, const Tuple &t);

    public:
        double _x;
        double _y;
        double _z;
        double _w;

        Tuple();
        Tuple(const double& x, const double& y, const double& z, const double& w);
        virtual ~Tuple() = default;

        inline bool is_point() const { return _w == 1.0; }
        inline bool is_vector() const { return _w == 0.0; } 
};

bool operator==(const Tuple& lhs, const Tuple& rhs);
Tuple operator+(const Tuple& lhs, const Tuple& rhs);
Tuple operator-(const Tuple& lhs, const Tuple& rhs);
Tuple operator-(const Tuple& orig);
Tuple operator*(const Tuple& lhs, const double& scalar);
Tuple operator/(const Tuple& lhs, const double& scalar);

Tuple create_point(const double& x, const double& y, const double& z);
Tuple create_vector(const double& x, const double& y, const double& z);

double magnitude(const Tuple &t);
Tuple normalize(const Tuple &t);
double dot(const Tuple &lhs, const Tuple &rhs);
Tuple cross(const Tuple &lhs, const Tuple &rhs);
Tuple reflect(const Tuple &in, const Tuple &normal);

#endif