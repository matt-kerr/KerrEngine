// Matthew Kerr
#include "Environment.h"
#include "Geometry.h"

using namespace std;

Environment::Environment(const Geometry& gravity, const Geometry& wind)
{
	this->gravity = gravity;
	this->wind = wind;
}

Environment::~Environment()
{

}