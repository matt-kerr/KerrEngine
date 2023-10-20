// Matthew Kerr

#ifndef GRADIENT_PATTERN_H
#define GRADIENT_PATTERN_H

#include <iostream>

#include "../primitives/color.h"
#include "pattern.h"

using namespace std;

class Color;
class Pattern;
class GradientPattern : public Pattern
{
    public:
        GradientPattern() : Pattern(white(), black()) { };
        virtual ~GradientPattern() = default;
        GradientPattern(const Color& a, const Color& b) : Pattern(a, b) { }
		GradientPattern(const Color& a, const Color& b, const Matrix& transform) : Pattern(a, b, transform) { }

        const Color Pattern::pattern_at(const Tuple &point) const { return _a + (_b - _a) * (point._x - std::floor(point._x)); }
};

#endif