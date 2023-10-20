#ifndef KERR_INLINE_H
#define KERR_INLINE_H

#include <numbers>
#include <string>
#include <math.h>

inline const int VERBOSE_DEBUG = 0;
inline const int VERBOSE_TEST = 1;
inline const int VERBOSE_CAMERA = 1;
inline const int REFLECTION_DEPTH = 1;
inline const double EPSILON = 0.00001;
inline const double BIG_NUM = 10e6;
inline const double SQRT_2 = (double)sqrt(2.0);
inline const double SQRT_2_OVER_2 = (double)sqrt(2.0) / 2.0;
inline const double SQRT_3_OVER_3 = (double)sqrt(3.0) / 3.0;
inline const double PI_OVER_6 = (double)std::numbers::pi / 6.0;
inline const double PI_OVER_5 = (double)std::numbers::pi / 5.0;
inline const double PI_OVER_4 = (double)std::numbers::pi / 4.0;
inline const double PI_OVER_3 = (double)std::numbers::pi / 3.0;
inline const double PI_OVER_2 = (double)std::numbers::pi / 2.0;
inline const double PI = (double)std::numbers::pi;
inline const double THREE_PI_OVER_2 = 3.0 * (double)std::numbers::pi / 2.0;
inline const double TWO_PI = 2.0 * (double)std::numbers::pi;

inline bool almost_equal(const double &a, const double &b) { return std::abs(a - b) < EPSILON; }
inline bool almost_equal(const int &a, const int &b) { return std::abs(a - b) < EPSILON; }
inline std::string bool_to_str(const bool &input) { return (input ? std::string("true") : std::string("false")); }

#endif