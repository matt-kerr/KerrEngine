// Matthew Kerr

#include "World.h"

World::World()
{
	this->light = PointLight(Matrix::point(-10.0, 10.0, -10.0), Color(1.0, 1.0, 1.0));
}

World::~World() { }