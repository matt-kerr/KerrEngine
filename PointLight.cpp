// Matthew Kerr

#include "KerrEngineException.h"
#include "PointLight.h"

PointLight::PointLight() { throw KerrEngineException(EXCEPTION_POINTLIGHT_NEEDS_PARAMETERS); }

PointLight::~PointLight() { }

PointLight::PointLight(Matrix position, Color intensity)
{
	this->position = position;
	this->intensity = intensity;
}