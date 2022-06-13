// Matthew Kerr

#include "Material.h"
#include "Color.h"
#include "KerrEngineException.h"

Material::Material()
{
	this->color = Color::create(1.0, 1.0, 1.0);
	this->ambient = 0.1;
	this->diffuse = 0.9;
	this->specular = 0.9;
	this->shininess = 200.0;
}

Material::~Material() { }

Material::Material(Color color, const double& ambient, const double& diffuse, const double& specular, const double& shininess)
{
	this->color = color;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

Color Material::lighting(PointLight light, Matrix point, Matrix eyev, Matrix normalv)
{
	Color black(0.0, 0.0, 0.0);
	Color effective_color = this->color * light.intensity;
	Matrix lightv = (light.position - point).normalize();
	Matrix reflectv;
	Color cont_ambient = effective_color * this->ambient;
	Color cont_diffuse, cont_specular;
	double light_dot_normal = lightv.dotProductVector(normalv);
	double reflect_dot_eye, factor;
	if (light_dot_normal < 0.0)
	{
		cont_diffuse = black;
		cont_specular = black;
	}
	else
	{
		cont_diffuse = effective_color * this->diffuse * light_dot_normal;
		reflectv = (lightv * -1.0).reflect(normalv);
		reflect_dot_eye = reflectv.dotProductVector(eyev);
		if (reflect_dot_eye <= 0.0)
		{
			cont_specular = black;
		}
		else
		{
			factor = pow(reflect_dot_eye, this->shininess);
			cont_specular = light.intensity * this->specular * factor;
		}
	}
	return cont_ambient + cont_diffuse + cont_specular;
}