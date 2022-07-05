// Matthew Kerr

#include "Material.h"

Material::Material()
{
	this->color = Color(1.0, 1.0, 1.0);
	this->ambient = 0.1;
	this->diffuse = 0.9;
	this->specular = 0.9;
	this->shininess = 200.0;
	this->reflective = 0.0;
	this->transparency = 0.0;
	this->refractive_index = 1.0;
}

Material::~Material() { }

Material::Material(Color color, Pattern pattern, const double& ambient
	, const double& diffuse, const double& specular, const double& shininess
	, const double& reflective, const double& transparency, const double& refractive_index)
{
	this->color = color;
	this->pattern = pattern;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
	this->reflective = reflective;
	this->transparency = transparency;
	this->refractive_index = refractive_index;
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
	this->reflective = orig.reflective;
	this->transparency = orig.transparency;
	this->refractive_index = orig.refractive_index;
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
	this->reflective = orig.reflective;
	this->transparency = orig.transparency;
	this->refractive_index = orig.refractive_index;
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
	this->reflective = rhs.reflective;
	this->transparency = rhs.transparency;
	this->refractive_index = rhs.refractive_index;
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
		this->reflective = orig.reflective;
		this->transparency = orig.transparency;
		this->refractive_index = orig.refractive_index;
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
		&&	(this->shininess == rhs.shininess)
		&&  (this->reflective == rhs.reflective)
		&&  (this->transparency == rhs.transparency)
		&& 	(this->refractive_index == rhs.refractive_index));
}