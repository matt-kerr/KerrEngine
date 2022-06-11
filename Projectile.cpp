// Matthew Kerr
#include "Projectile.h"
#include "Geometry.h"
#include "Environment.h"

using namespace std;

Projectile::Projectile(const Geometry& position, const Geometry& velocity)
{
	this->position = position;
	this->velocity = velocity;
}

Projectile::~Projectile()
{

}

Projectile& Projectile::operator=(const Projectile& orig)
{
	this->position = orig.position;
	this->velocity = orig.velocity;
	return *this;
}

Projectile Projectile::tick(const Environment& env, const Projectile& orig)
{
	Projectile result((orig.position + orig.velocity), (orig.velocity + env.gravity + env.wind));
	if (result.position.y < 0.0)
	{
		result.position.y = 0.0;
		result.velocity.x = 0.0;
		result.velocity.y = 0.0;
		result.velocity.z = 0.0;
	}
	return result;
}