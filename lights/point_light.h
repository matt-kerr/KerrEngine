// Matthew Kerr

#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "light.h"

class Light;
class PointLight : public Light
{
	public:
		PointLight() { }
		PointLight(const Tuple &position, const Color &intensity) : Light(position, intensity) { }
		virtual ~PointLight() = default;
};

#endif