// Matthew Kerr

#ifndef RAY_H
#define RAY_H

#include <vector>
#include "Matrix.h"
#include "Sphere.h"
#include "Intersection.h"
#include "KerrEngineException.h"
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
		static Matrix position(const Ray& r, const double& t);
		static std::vector<Intersection> intersectSphere(const Ray& r, Sphere s);
		static Ray transform(const Ray& r, const Matrix& m);
};

#endif

