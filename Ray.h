// Matthew Kerr

#ifndef RAY_H
#define RAY_H

#include "Ray.h"
#include "Matrix.h"
#include "Sphere.h"
#include "Intersection.h"
using namespace std;

class Ray
{
	public:
		Matrix origin; // point
		Matrix direction; // vector

		// constructors
		Ray();
		virtual ~Ray();
		Ray(Matrix origin, Matrix direction);

		// ray functions
		Matrix position(const double& t);
		Intersection* intersectSphere(Sphere *s);
		Ray transform(Matrix m);
};

#endif

