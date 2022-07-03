// Matthew Kerr

#include "Material.h"

Material::Material()
{
	this->ambient = 0.1;
	this->diffuse = 0.9;
	this->specular = 0.9;
	this->shininess = 200.0;
}

Material::~Material() { }

Material::Material(Color color, Pattern pattern, const double& ambient, const double& diffuse, const double& specular, const double& shininess)
{
	this->color = color;
	this->pattern = pattern;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

// copy constructor
Material::Material(Material& orig)
{
	this->color = orig.color;
	this->pattern = orig.pattern;
	this->ambient = orig.ambient;
	this->diffuse = orig.diffuse;
	this->specular = orig.specular;
	this->shininess = orig.shininess;
}

// move constructor
Material::Material(Material&& orig) noexcept
{
	this->color = orig.color;
	this->pattern = orig.pattern;
	this->ambient = orig.ambient;
	this->diffuse = orig.diffuse;
	this->specular = orig.specular;
	this->shininess = orig.shininess;
}

// = operator overload
Material& Material::operator=(const Material& rhs)
{
	this->color = rhs.color;
	this->pattern = rhs.pattern;
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
		this->pattern = orig.pattern;
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
		&&  (this->pattern == rhs.pattern)
		&&  (this->ambient == rhs.ambient)
		&&	(this->diffuse == rhs.diffuse)
		&&	(this->specular == rhs.specular)
		&&	(this->shininess == rhs.shininess));
}