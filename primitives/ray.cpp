// Matthew Kerr

#include "ray.h"

std::ostream& operator<<(std::ostream &out, const Ray &r) {
    std::cout << "Ray:" << std::endl
              << "  origin: " << r._origin << std::endl
              << "  direction: " << r._direction << std::endl;
    return out;
}

Ray::Ray(const Tuple &origin, const Tuple &direction) {
    _origin = origin;
    _direction = direction;
}

Tuple position(const Ray &ray, const double &t) {
    return ray._origin + ray._direction * t;
}

Ray transform_ray(const Ray &ray, const Matrix &m) {
    return Ray(m * ray._origin, m * ray._direction);
}
