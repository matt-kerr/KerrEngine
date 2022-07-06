// Matthew Kerr

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Color.h"
#include "PointLight.h"
#include "Shape.h"
#include "Sphere.h"
#include "Plane.h"

class World
{
	public:
		PointLight light;
		std::vector<Shape*> shapes;

		// constructors
		World();
		virtual ~World();

		// world functions
		static void clearWorld(World w);
		static World defaultWorld();
};

#endif;