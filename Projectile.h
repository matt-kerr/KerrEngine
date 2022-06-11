// Matthew Kerr
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Geometry.h"
#include "Environment.h"
using namespace std;

class Projectile
{
	public:
		Geometry position; // point
		Geometry velocity; // vector
		Projectile(const Geometry& position, const Geometry& velocity);
		virtual ~Projectile();
		Projectile& operator=(const Projectile& orig);
		static Projectile tick(const Environment& env, const Projectile& orig);
};

#endif