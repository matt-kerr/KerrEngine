// Matthew Kerr

#include "tuple.h"

std::ostream& operator<<(std::ostream &out, const Tuple &t) {
    std::cout << "Tuple(" << t._x << ", " << t._y << ", " << t._z << ", " << t._w << ")";
    return out;
}

Tuple::Tuple() {
    _x = 0.0;
    _y = 0.0;
    _z = 0.0;
    _w = 0.0;
}

Tuple::Tuple(const double& x, const double& y, const double& z, const double& w) {
    _x = x;
    _y = y;
    _z = z;
    _w = w;
}

bool operator==(const Tuple& lhs, const Tuple& rhs) {
    return almost_equal(lhs._x, rhs._x) && almost_equal(lhs._y, rhs._y) && almost_equal(lhs._z, rhs._z) && almost_equal(lhs._w, rhs._w);
}

Tuple operator+(const Tuple& lhs, const Tuple& rhs) {
    return Tuple(lhs._x + rhs._x, lhs._y + rhs._y, lhs._z + rhs._z, lhs._w + rhs._w);
}

Tuple operator-(const Tuple& lhs, const Tuple& rhs) {
    return Tuple(lhs._x - rhs._x, lhs._y - rhs._y, lhs._z - rhs._z, lhs._w - rhs._w);
}

Tuple operator-(const Tuple& orig) {
    return Tuple(orig._x * -1.0, orig._y * -1.0, orig._z * -1.0, orig._w * -1.0);
}

Tuple operator*(const Tuple& lhs, const double& scalar) {
    return Tuple(lhs._x * scalar, lhs._y * scalar, lhs._z * scalar, lhs._w * scalar);
}

Tuple operator/(const Tuple& lhs, const double& scalar) {
   return Tuple(lhs._x / scalar, lhs._y / scalar, lhs._z / scalar, lhs._w / scalar);
}

Tuple create_point(const double& x, const double& y, const double& z) {
    return Tuple(x, y, z, 1.0);
}

Tuple create_vector(const double& x, const double& y, const double& z) {
    return Tuple(x, y, z, 0.0);
}

double magnitude(const Tuple &t) {
    return std::sqrt(std::pow(t._x, 2.0) + std::pow(t._y, 2.0) + std::pow(t._z, 2.0));
}

Tuple normalize(const Tuple &t) {
    double mag = magnitude(t);
	return create_vector(t._x / mag, t._y / mag, t._z / mag);
}

double dot(const Tuple &lhs, const Tuple &rhs) {
    return lhs._x * rhs._x + lhs._y * rhs._y + lhs._z * rhs._z + lhs._w * rhs._w;
}

Tuple cross(const Tuple &lhs, const Tuple &rhs) {
    return create_vector(lhs._y * rhs._z - lhs._z * rhs._y, lhs._z * rhs._x - lhs._x * rhs._z, lhs._x * rhs._y - lhs._y * rhs._x);
}

Tuple reflect(const Tuple &in, const Tuple &normal) {
    return in - normal * 2.0 * dot(in, normal);
}