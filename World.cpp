// Matthew Kerr

#include <algorithm>
#include <vector>
#include "KerrEngineException.h"
#include "Intersection.h"
#include "Ray.h"
#include "World.h"
#include "Matrix.h"
#include "Color.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Computations.h"

World::World()
{
	this->light = PointLight(Matrix::point(-10.0, 10.0, -10.0), Color::create(1.0, 1.0, 1.0));
	//Sphere s1, s2;
	//s1.material.color = Color::create(0.8, 1.0, 0.6);
	//s1.material.diffuse = 0.7;
	//s1.material.specular = 0.2;
	//s2.transform = Matrix::scaling(0.5, 0.5, 0.5);
	//this->spheres.push_back(s1);
	//this->spheres.push_back(s2);
}

World::~World() { }


std::vector<Intersection> World::intersectWorld(World w, const Ray& r)
{
	std::vector<Intersection> xs, curr;
	for (int i = 0; i < w.spheres.size(); i++)
	{
		curr = Ray::intersectSphere(r, w.spheres[i]);
		if (curr.size() > 0)
		{
			xs.push_back(curr[0]);
			xs.push_back(curr[1]);
		}
	}
	std::sort(xs.begin(), xs.end());
	return xs;
}

Color World::shadeHit(const World& world, const Computations& comps)
{
	return Material::lighting(comps.obj.material, world.light, comps.point, comps.eyev, comps.normalv);
	throw KerrEngineException("Unsupported object type in World::shadeHit");
}

Color World::colorAt(World world, const Ray& ray)
{
	std::vector<Intersection> xs = World::intersectWorld(world, ray);
	if (xs.size() == 0)
	{
		return Color::create(0.0, 0.0, 0.0);
	}
	Intersection i = Intersection::hit(xs);
	if (i.t < 0.0) { return Color::create(0.0, 0.0, 0.0); }
	Computations comps = Computations::prepareComputations(i, ray);
	return World::shadeHit(world, comps);
}