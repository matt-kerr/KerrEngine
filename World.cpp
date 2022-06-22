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
	if (DEBUG) { cout << "    World::intersectWorld entered" << endl; }
	std::vector<Intersection> xs, curr;
	for (int i = 0; i < w.spheres.size(); i++)
	{
		if (DEBUG) { cout << "    World::intersectWorld testing sphere " << i + 1 << endl; }
		curr = Ray::intersectSphere(r, w.spheres[i]);
		if (DEBUG) { cout << "    World::intersectWorld curr.size() = " << curr.size() << endl; }
		if (curr.size() > 0)
		{
			xs.push_back(curr[0]);
			xs.push_back(curr[1]);
		}
		if (DEBUG) { cout << "    World::intersectWorld xs.size() = " << xs.size() << endl; }
	}
	if (xs.size() == 0)
	{
		if (DEBUG) { cout << "    World::intersectWorld xs.size() = 0, returning early" << endl; }
		return xs;
	}
	std::sort(xs.begin(), xs.end());
	if (DEBUG)
	{
		cout << "    World::intersectWorld after sort:" << endl;
		for (int i = 0; i < xs.size(); i++)
		{
			cout << "            xs[" << i << "].t = " << xs[i].t << endl;
		}
	}
	if (DEBUG) { cout << "    World::intersectWorld exiting" << endl; }
	return xs;
}

Color World::shadeHit(const World& world, const Computations& comps)
{
	if (DEBUG) { cout << "World::shadeHit comps.t = " << comps.t << endl; }
	bool shadowed = World::isShadowed(world, comps.over_point);
	if (DEBUG)
	{
		cout << "World::shadeHit comps.t = " << comps.t << endl;
		cout << "World::shadeHit comps.point = " << comps.point;
		cout << "World::shadeHit comps.over_point = " << comps.over_point;
		cout << "World::shadeHit shadowed = " << shadowed << endl;
	}
	Color ret = Material::lighting(comps.obj.material, world.light, comps.over_point, comps.eyev, comps.normalv, shadowed);
	if (DEBUG) { cout << "World::shadeHit returning " << ret << endl; }
	return ret;
}

Color World::colorAt(const World& world, const Ray& ray)
{
	if (DEBUG) { cout << "World::colorAt entered function, calculating world/ray intersection" << endl; }
	std::vector<Intersection> xs = World::intersectWorld(world, ray);
	if (DEBUG)
	{
		cout << "World::colorAt xs.size() = " << xs.size() << endl;
		for (int i = 0; i < xs.size(); i++)
		{
			cout << "World::colorAt xs[" << i << "].t = " << xs[i].t << endl;
		}
	}
	if (xs.size() == 0) { return Color::create(0.0, 0.0, 0.0); }

	Intersection i = Intersection::hit(xs);
	if (i.t < 0.0) { return Color::create(0.0, 0.0, 0.0); }
	Computations comps = Computations::prepareComputations(i, ray);
	if (DEBUG)
	{
		cout << "World::colorAt i.t = " << i.t << endl;
		cout << "World::colorAt comps.t = " << comps.t << endl;
		cout << "World::colorAt calculating shadeHit = " << comps.t << endl;
	}
	return World::shadeHit(world, comps);
}

bool World::isShadowed(const World& world, const Matrix& point)
{
	if (DEBUG) { cout << "World::isShadowed entered" << endl; }
	Matrix v = world.light.position - point;
	double distance = Matrix::magnitude(v);
	Matrix direction = Matrix::normalize(v);
	Ray r(point, direction);
	std::vector<Intersection> xs = World::intersectWorld(world, r);
	Intersection h = Intersection::hit(xs);
	if (h.t == -999.0)
	{
		if (DEBUG) { cout << "World::isShadowed no hits, returning early" << endl; }
		return false;
	}
	double ht_adj = (std::abs(h.t) < EPSILON) ? 0.0 : h.t;
	if (DEBUG)
	{
		cout << "World::isShadowed world.light.position = " << world.light.position;
		cout << "World::isShadowed point = " << point;
		cout << "World::isShadowed v = " << v;
		cout << "World::isShadowed distance = " << distance << endl;
		cout << "World::isShadowed direction = " << direction;
		cout << "World::isShadowed xs.size() = " << xs.size() << endl;
		for (int i = 0; i < xs.size(); i++)
		{
			cout << "World::isShadowed xs[" << i << "].t = " << xs[i].t << endl;
		}
		cout << "World::isShadowed ht_adj = " << ht_adj << endl;
	}
	if (ht_adj > 0.0 && ht_adj < distance)
	{
		if (DEBUG) { cout << "World::isShadowed returning true" << endl; }
		//system("pause");
		return true;
	}
	if (DEBUG) { cout << "World::isShadowed returning false" << endl; }
	
	return false;
}