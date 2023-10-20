#ifndef LIGHT_H
#define LIGHT_H

#include "../primitives/color.h"
#include "../primitives/tuple.h"

class Color;
class Tuple;
class Light
{
    public:
		Tuple _position;
		Color _intensity;	

		Light();
		Light(const Tuple &position, const Color &intensity);
		virtual ~Light() = default;		
};

#endif