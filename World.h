// Matthew Kerr

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Intersection.h"
#include "Ray.h"
#include "Matrix.h"
#include "Color.h"
#include "PointLight.h"
#include "Sphere.h"
using namespace std;

class World
{
	public:
		PointLight light;
		std::vector<Sphere> spheres;

		// constructors
		World();
		virtual ~World();

		// world functions
		static std::vector<Intersection> intersectWorld(World w, const Ray& r);
};

#endif;