// Matthew Kerr

#include <iostream>
#include "KerrEngine.h"
using namespace std;

KerrEngine::KerrEngine() { }

bool KerrEngine::almost_equal(const double& a, const double& b)
{
	return std::abs(a - b) < EPSILON;
}