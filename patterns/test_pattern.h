// Matthew Kerr

#ifndef TEST_PATTERN_H
#define TEST_PATTERN_H

#include <iostream>

#include "../primitives/color.h"
#include "pattern.h"

using namespace std;

class Color;
class Pattern;
class TestPattern : public Pattern
{
    public:
        TestPattern() : Pattern(white(), black()) { };
        virtual ~TestPattern() = default;
        TestPattern(const Color& a, const Color& b) : Pattern(a, b) { }
		TestPattern(const Color& a, const Color& b, const Matrix& transform) : Pattern(a, b, transform) { }

        const Color Pattern::pattern_at(const Tuple &point) const { return Color(point._x, point._y, point._z); }
};

#endif