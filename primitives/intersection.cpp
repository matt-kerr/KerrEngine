#include "intersection.h"

std::ostream& operator<<(std::ostream &out, const Intersection &i) {
    std::cout << "Intersection:" << std::endl
              << "  t: " << i._t << std::endl
              << "  obj: " << i._obj << std::endl;
    return out;
}

Intersection::Intersection(const double &t, void *obj) {
    _t = t;
    _obj = obj;
}

bool operator==(const Intersection &lhs, const Intersection &rhs) {
    return almost_equal(lhs._t, rhs._t) && lhs._obj == rhs._obj;
}