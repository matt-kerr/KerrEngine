// Matthew Kerr

#include "World.h"

World::World()
{
	this->light = PointLight(Matrix::point(-10.0, 10.0, -10.0), Color(1.0, 1.0, 1.0));
	/*
	Sphere* s1_ptr = new Sphere();
	Sphere* s2_ptr = new Sphere();
	s1_ptr->material.color = Color(0.8, 1.0, 0.6);
	s1_ptr->material.diffuse = 0.7;
	s1_ptr->material.specular = 0.2;
	s2_ptr->transform = Matrix::scaling(0.5, 0.5, 0.5);
	shapes.push_back(s1_ptr);
	shapes.push_back(s2_ptr);
	*/
}

World::~World()
{
	for (int i = 0; i < shapes.size(); i++)
	{
		delete shapes[0];
		shapes.erase(shapes.begin());
	}
}