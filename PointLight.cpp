// Matthew Kerr

#include "PointLight.h"

PointLight::PointLight()
{
	this->intensity = Color(1.0, 1.0, 1.0);
	this->position = Matrix::point(0.0, 0.0, 0.0);
}

PointLight::~PointLight() { }

PointLight::PointLight(Matrix position, Color intensity)
{
	this->position = position;
	this->intensity = intensity;
}