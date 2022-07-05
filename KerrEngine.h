// Matthew Kerr

#ifndef KERRENGINE_H
#define KERRENGINE_H
#define EPSILON 0.00001
#define VECTOR 0
#define POINT 1
#define REFLECTION_DEPTH 5
#define SQRT_2 std::sqrt(2)
#define SQRT_2_OVER_2 std::sqrt(2) / 2
#define PI_OVER_6 std::numbers::pi / 6
#define PI_OVER_4 std::numbers::pi / 4
#define PI_OVER_3 std::numbers::pi / 3
#define PI_OVER_2 std::numbers::pi / 2
#define PI std::numbers::pi
#define THREE_PI_OVER_2 (3.0 * std::numbers::pi) / 2
#define TWO_PI 2.0 * std::numbers::pi
#define DEBUG 0
#define DEBUG2 0

using namespace std;

class KerrEngine
{
	public:
		KerrEngine();
		static bool almost_equal(const double& a, const double& b);
};

#endif
