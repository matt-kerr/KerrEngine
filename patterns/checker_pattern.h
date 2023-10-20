// Matthew Kerr

#ifndef CHECKER_PATTERN_H
#define CHECKER_PATTERN_H

#include <iostream>

#include "../primitives/color.h"
#include "pattern.h"

using namespace std;

class Color;
class Pattern;
class CheckerPattern : public Pattern
{
    public:
        CheckerPattern() : Pattern(white(), black()) { };
        virtual ~CheckerPattern() = default;
        CheckerPattern(const Color& a, const Color& b) : Pattern(a, b) { }
		CheckerPattern(const Color& a, const Color& b, const Matrix& transform) : Pattern(a, b, transform) { }

        const Color Pattern::pattern_at(const Tuple &point) const { return ((int)(std::floor(point._x) + std::floor(point._y) + std::floor(point._z)) % 2 == 0) ? _a : _b; }
};

#endif