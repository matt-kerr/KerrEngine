// Matthew Kerr

#ifndef KERRENGINE_H
#define KERRENGINE_H
#define EPSILON 0.00001
#define VECTOR 0
#define POINT 1

using namespace std;

class KerrEngine
{
	public:
		KerrEngine();
		static bool almost_equal(const double& a, const double& b);
};

#endif
