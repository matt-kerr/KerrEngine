// Matthew Kerr

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"
#include "Pattern.h"

class Material
{
	public:
		Color color;
		Pattern pattern;
		double ambient;
		double diffuse;
		double specular;
		double shininess;
		double reflective;
		double transparency;
		double refractive_index;

		// constructors
		Material();
		virtual ~Material();
		Material(Color color, Pattern pattern, const double& ambient
				, const double& diffuse, const double& specular, const double& shininess
				, const double& reflective, const double& transparency, const double& refractive_index);

		Material(Material& orig); // copy constructor
		Material(Material&& orig) noexcept; // move constructor

		// operator overloads
		Material& operator=(const Material& rhs); // = operator overload
		Material& operator=(Material&& orig); // move = operator overload (move assignment overload)
		bool operator==(const Material& rhs); // == operator overload
};

#endif