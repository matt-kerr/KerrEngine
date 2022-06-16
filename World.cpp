// Matthew Kerr

#include <algorithm>
#include <vector>
#include "Intersection.h"
#include "Ray.h"
#include "World.h"
#include "Matrix.h"
#include "Color.h"
#include "PointLight.h"
#include "Sphere.h"

World::World()
{
	this->light.position = Matrix::point(-10.0, 10.0, -10.0);
	this->light.intensity = Color::create(1.0, 1.0, 1.0);
	Sphere s1, s2;
	s1.material.color = Color::create(0.8, 1.0, 0.6);
	s1.material.diffuse = 0.7;
	s1.material.specular = 0.2;
	s2.transform = Matrix::scaling(0.5, 0.5, 0.5);
	this->spheres.push_back(s1);
	this->spheres.push_back(s2);
}

World::~World() { }


std::vector<Intersection> World::intersectWorld(World w, const Ray& r)
{
	std::vector<Intersection> xs, curr;
	for (int i = 0; i < w.spheres.size(); i++)
	{
		curr = Ray::intersectSphere(r, &w.spheres[i]);
		if (curr.size() > 0)
		{
			xs.push_back(curr[0]);
			xs.push_back(curr[1]);
		}
	}
	std::sort(xs.begin(), xs.end());
	return xs;
}
