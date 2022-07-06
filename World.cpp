// Matthew Kerr

#include "World.h"

World::World() { }

World::~World() { }

void World::clearWorld(World w)
{
	for (int i = 0; i < w.shapes.size(); i++)
	{
		delete w.shapes[i];
	}
	w.shapes.clear();
}

World World::defaultWorld()
{
	World w;
	w.light = PointLight(Matrix::point(-10.0, 10.0, -10.0), Color(1.0, 1.0, 1.0));
	Sphere* s1_ptr = new Sphere();
	Sphere* s2_ptr = new Sphere();
	s1_ptr->material.color = Color(0.8, 1.0, 0.6);
	s1_ptr->material.diffuse = 0.7;
	s1_ptr->material.specular = 0.2;
	s2_ptr->transform = Matrix::scaling(0.5, 0.5, 0.5);
	w.shapes.push_back(s1_ptr);
	w.shapes.push_back(s2_ptr);
	return w;
}