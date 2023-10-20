// Matthew Kerr

#include "material.h"

std::ostream& operator<<(std::ostream &out, const Material &m) {
	std::cout << "Material:" << std::endl
			  << "  color: " << m._color
			  << "  pattern: ";
	if (m._pattern != nullptr) {
		std::cout << m._pattern;
	} else {
		std::cout << "null" << std::endl;
	}
	std::cout << "  ambient: " << m._ambient << std::endl
		 	<< "  diffuse: " << m._diffuse << std::endl
			<< "  specular: " << m._specular << std::endl
			<< "  shininess: " << m._shininess << std::endl
			<< "  reflective: " << m._reflective << std::endl
			<< "  transparency: " << m._transparency << std::endl
			<< "  refractive_index: " << m._refractive_index << std::endl;
    return out;
}

Material::Material() {
	_color = Color(1.0, 1.0, 1.0);
	_ambient = 0.1;
	_diffuse = 0.9;
	_specular = 0.9;
	_shininess = 200.0;
	_reflective = 0.0;
	_transparency = 0.0;
	_refractive_index = 1.0;
}

Material::Material(const Color &color, Pattern *pattern, const double &ambient
				, const double &diffuse, const double &specular, const double &shininess
				, const double &reflective, const double &transparency, const double &refractive_index) {
	_color = color;
	_pattern = pattern;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_shininess = shininess;
	_reflective = reflective;
	_transparency = transparency;
	_refractive_index = refractive_index;
}

Material::~Material() {
	if (_pattern != nullptr) { delete _pattern; }
}

bool operator==(const Material &lhs, const Material &rhs) {
	
	if ((lhs._color == rhs._color)
		&&  (lhs._ambient == rhs._ambient)
		&&	(lhs._diffuse == rhs._diffuse)
		&&	(lhs._specular == rhs._specular)
		&&	(lhs._shininess == rhs._shininess)
		&&  (lhs._reflective == rhs._reflective)
		&&  (lhs._transparency == rhs._transparency)
		&& 	(lhs._refractive_index == rhs._refractive_index)) {
		if (lhs._pattern == nullptr && rhs._pattern == nullptr) { return true; }
		else if ((lhs._pattern == nullptr && rhs._pattern != nullptr) || (lhs._pattern != nullptr && rhs._pattern == nullptr)) { return false; }
		return (*lhs._pattern) == (*rhs._pattern);
	}
	return false;
}