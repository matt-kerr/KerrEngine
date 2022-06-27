// Matthew Kerr

#include <algorithm>
#include <vector>
#include <iostream>

#include "World.h"
#include "KerrEngine.h"
#include "KerrEngineException.h"
#include "Intersection.h"
#include "Ray.h"
#include "Matrix.h"
#include "Color.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Computations.h"

World::World()
{
	PointLight pl(Matrix::point(-10.0, 10.0, -10.0), Color::create(1.0, 1.0, 1.0));
	this->light = pl;
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
	if (xs.size() == 0) { return xs; }
	std::sort(xs.begin(), xs.end());
	return xs;
}

Color World::shadeHit(const World& world, const Computations& comps)
{
	bool shadowed = World::isShadowed(world, comps.over_point);
	Color ret = Material::lighting(comps.obj.material, world.light, comps.over_point, comps.eyev, comps.normalv, shadowed);
	return ret;
}

Color World::colorAt(const World& world, const Ray& ray)
{
	std::vector<Intersection> xs = World::intersectWorld(world, ray);
	if (xs.size() == 0) { return Color::create(0.0, 0.0, 0.0); }
	Intersection i = Intersection::hit(xs);
	if (i.t < 0.0) { return Color::create(0.0, 0.0, 0.0); }
	Computations comps = Computations::prepareComputations(i, ray);
	return World::shadeHit(world, comps);
}

bool World::isShadowed(const World& world, const Matrix& point)
{
	Matrix v = world.light.position - point;
	double distance = Matrix::magnitude(v);
	Matrix direction = Matrix::normalize(v);
	Ray r(point, direction);
	std::vector<Intersection> xs = World::intersectWorld(world, r);
	Intersection h = Intersection::hit(xs);
	if (h.t == -999.0) { return false; }
	double ht_adj = (std::abs(h.t) < EPSILON) ? 0.0 : h.t;
	if (ht_adj > 0.0 && ht_adj < distance) { return true; }	
	return false;
}