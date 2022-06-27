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

// copy constructor
Material::Material(Material& orig)
{
	this->color = orig.color;
	this->ambient = orig.ambient;
	this->diffuse = orig.diffuse;
	this->specular = orig.specular;
	this->shininess = orig.shininess;
}

// move constructor
Material::Material(Material&& orig) noexcept
{
	this->color = orig.color;
	this->ambient = orig.ambient;
	this->diffuse = orig.diffuse;
	this->specular = orig.specular;
	this->shininess = orig.shininess;
}

// = operator overload
Material& Material::operator=(const Material& rhs)
{
	this->color = rhs.color;
	this->ambient = rhs.ambient;
	this->diffuse = rhs.diffuse;
	this->specular = rhs.specular;
	this->shininess = rhs.shininess;
	return *this;
}

// move = operator overload (move assignment overload)
Material& Material::operator=(Material&& orig)
{
	if (this != &orig)
	{
		this->color = orig.color;
		this->ambient = orig.ambient;
		this->diffuse = orig.diffuse;
		this->specular = orig.specular;
		this->shininess = orig.shininess;
	}
	return *this;
}

// == operator overload
bool Material::operator==(const Material& rhs)
{
	return ((this->color == rhs.color)
		&&  (this->ambient == rhs.ambient)
		&&	(this->diffuse == rhs.diffuse)
		&&	(this->specular == rhs.specular)
		&&	(this->shininess == rhs.shininess));
}

Color Material::lighting(const Material& material, const PointLight& light, const Matrix& point, const Matrix& eyev, const Matrix& normalv, const bool& in_shadow)
{
	Color black(0.0, 0.0, 0.0);
	Color effective_color = material.color * light.intensity;
	Matrix lightv = Matrix::normalize(light.position - point);
	Color cont_ambient = effective_color * material.ambient;
	if (in_shadow) { return cont_ambient; }
	Color cont_diffuse, cont_specular;
	double light_dot_normal = Matrix::dot(lightv, normalv);
	double reflect_dot_eye, factor;
	if (light_dot_normal < 0.0)
	{
		cont_diffuse = black;
		cont_specular = black;
	}
	else
	{
		cont_diffuse = effective_color * material.diffuse * light_dot_normal;
		Matrix reflectv = Matrix::reflect(-lightv, normalv);
		reflect_dot_eye = Matrix::dot(reflectv, eyev);
		if (reflect_dot_eye <= 0.0)
		{
			cont_specular = black;
		}
		else
		{
			factor = pow(reflect_dot_eye, material.shininess);
			cont_specular = light.intensity * material.specular * factor;
		}
	}
	return cont_ambient + cont_diffuse + cont_specular;
}