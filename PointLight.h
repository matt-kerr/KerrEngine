// Matthew Kerr

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Color.h"
#include "Matrix.h"

class PointLight
{
	public:
		Color intensity;
		Matrix position;

		// constructors
		PointLight();
		virtual ~PointLight();
		PointLight(Matrix position, Color intensity);
};

#endif