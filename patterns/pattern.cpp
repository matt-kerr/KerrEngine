// Matthew Kerr

#include "pattern.h"

std::ostream& operator<<(std::ostream &out, const Pattern &p) {
    std::cout << typeid(p).name() << " (Pattern):" << std::endl
			  << "a: " << p._a
			  << "b: " << p._b
			  << "transform:" << std::endl
			  << p._transform
			  << "  active: " << bool_to_str(p._active) << std::endl;
    return out;
}

Pattern::Pattern() {
	_active = false;
}

Pattern::Pattern(const Color& a, const Color& b) {
	_a = a;
	_b = b;
	_active = true;
}

Pattern::Pattern(const Color& a, const Color& b, const Matrix& transform) {
	_a = a;
	_b = b;
	_transform = transform;
	_active = true;
}

bool operator==(const Pattern &lhs, const Pattern& rhs) {
	if (!lhs._active || !rhs._active) { return false; }
	return lhs._a == rhs._a && lhs._b == rhs._b && lhs._transform == rhs._transform;
}