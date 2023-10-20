#include "light.h"

Light::Light() {
	_position = create_point(0.0, 0.0, 0.0);
	_intensity = Color(1.0, 1.0, 1.0);
}

Light::Light(const Tuple &position, const Color &intensity) {
	_position = position;
	_intensity = intensity;
}