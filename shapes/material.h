// Matthew Kerr

#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include "../lights/light.h"
#include "../patterns/pattern.h"
#include "../primitives/color.h"

class Color;
class Light;
class Pattern;
class Material
{
	friend std::ostream& operator<<(std::ostream &out, const Material &m);

	public:
		Color _color;
		Pattern *_pattern = nullptr;
		double _ambient;
		double _diffuse;
		double _specular;
		double _shininess;
		double _reflective;
		double _transparency;
		double _refractive_index;

		Material();
		Material(const Color &color, Pattern *pattern, const double &ambient
				, const double &diffuse, const double &specular, const double &shininess
				, const double &reflective, const double &transparency, const double &refractive_index);		
		~Material();
};

bool operator==(const Material &lhs, const Material &rhs);

#endif