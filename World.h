// Matthew Kerr

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "PointLight.h"
#include "Sphere.h"

class World
{
	public:
		PointLight light;
		std::vector<Shape*> shapes;

		// constructors
		World();
		virtual ~World();
};

#endif;