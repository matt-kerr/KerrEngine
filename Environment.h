// Matthew Kerr
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Geometry.h"
using namespace std;

class Environment
{
	public:
		Geometry gravity; // vector
		Geometry wind; // vector
		Environment(const Geometry& gravity, const Geometry& wind);
		virtual ~Environment();
};

#endif