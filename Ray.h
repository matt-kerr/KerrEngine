// Matthew Kerr

#ifndef RAY_H
#define RAY_H

#include "Matrix.h"

class Ray
{
	public:
		Matrix origin; // point
		Matrix direction; // vector

		// constructors
		Ray();
		virtual ~Ray();
		Ray(Matrix origin, Matrix direction);
};

#endif

