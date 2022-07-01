// Matthew Kerr

#include "Material.h"

Material::Material()
{
	this->color = Color(1.0, 1.0, 1.0);
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