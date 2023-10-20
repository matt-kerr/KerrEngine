// Matthew Kerr

#ifndef RING_PATTERN_H
#define RING_PATTERN_H

#include <iostream>

#include "../primitives/color.h"
#include "pattern.h"

using namespace std;

class Color;
class Pattern;
class RingPattern : public Pattern
{
    public:
        RingPattern() : Pattern(white(), black()) { };
        virtual ~RingPattern() = default;
        RingPattern(const Color& a, const Color& b) : Pattern(a, b) { }
		RingPattern(const Color& a, const Color& b, const Matrix& transform) : Pattern(a, b, transform) { }

        const Color Pattern::pattern_at(const Tuple &point) const { return ((int)std::floor(std::sqrt(std::pow(point._x, 2.0) + std::pow(point._z, 2.0))) % 2 == 0) ? _a : _b; }
};

#endif