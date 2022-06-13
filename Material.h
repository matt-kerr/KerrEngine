// Matthew Kerr

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"
#include "Matrix.h"
#include "PointLight.h"

class Material
{
	public:
		Color color;
		double ambient, diffuse, specular, shininess;

		Material();
		virtual ~Material();
		Material(Color color, const double& ambient, const double& diffuse, const double& specular, const double& shininess);
		Color lighting(PointLight light, Matrix point, Matrix eyev, Matrix normalv);
};

#endif