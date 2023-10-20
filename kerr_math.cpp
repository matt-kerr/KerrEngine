// Matthew Kerr

#include "kerr_math.h"

std::vector<double> check_axis(double origin, double direction, double min, double max) {
	std::vector<double> ret;
	double tmin = 0.0;
	double tmax = 0.0;
	double tmin_numerator = min - origin;
	double tmax_numerator = max - origin;
	if (std::abs(direction) >= EPSILON) {
		tmin = tmin_numerator / direction;
		tmax = tmax_numerator / direction;
	}
	else {
		tmin = tmin_numerator * BIG_NUM;
		tmax = tmax_numerator * BIG_NUM;
	}
	ret.push_back(tmin);
	ret.push_back(tmax);
	if (tmin > tmax) { std::reverse(ret.begin(), ret.end()); }
	return ret;
}