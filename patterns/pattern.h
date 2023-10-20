// Matthew Kerr

#ifndef PATTERN_H
#define PATTERN_H

#include <iostream>
#include <string>
#include "../primitives/color.h"
#include "../primitives/tuple.h"
#include "../primitives/matrix.h"

class Color;
class Tuple;
class Matrix;
class Pattern
{
	friend std::ostream& operator<<(std::ostream &out, const Pattern &p);

	public:
		Color _a;
		Color _b;
		Matrix _transform = identity_matrix(4);
		bool _active;

		Pattern();
		Pattern(const Color& a, const Color& b);
		Pattern(const Color& a, const Color& b, const Matrix& transform);
		virtual ~Pattern() = default;
		
		virtual const Color pattern_at(const Tuple &point) const = 0;
};

bool operator==(const Pattern &lhs, const Pattern& rhs);

#endif