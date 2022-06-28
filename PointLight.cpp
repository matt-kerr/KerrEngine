// Matthew Kerr

#include "PointLight.h"
using namespace std;

PointLight::PointLight()
{
	this->intensity = Color::create(1.0, 1.0, 1.0);
	this->position = Matrix::point(0.0, 0.0, 0.0);
}

PointLight::~PointLight() { }

PointLight::PointLight(Matrix position, Color intensity)
{
	this->position = position;
	this->intensity = intensity;
}