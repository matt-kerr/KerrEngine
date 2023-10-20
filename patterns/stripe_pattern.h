// Matthew Kerr

#ifndef STRIPE_PATTERN_H
#define STRIPE_PATTERN_H

#include <iostream>

#include "../primitives/color.h"
#include "pattern.h"

using namespace std;

class Color;
class Pattern;
class StripePattern : public Pattern
{
    public:
        StripePattern() : Pattern(white(), black()) { };
        virtual ~StripePattern() = default;
        StripePattern(const Color& a, const Color& b) : Pattern(a, b) { }
		StripePattern(const Color& a, const Color& b, const Matrix& transform) : Pattern(a, b, transform) { }

        const Color Pattern::pattern_at(const Tuple &point) const { return ((int)std::floor(point._x) % 2 == 0) ? _a : _b; }
};

#endif