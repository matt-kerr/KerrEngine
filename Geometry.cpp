// Matthew Kerr

#include <iostream>
#include <string>
#include "Geometry.h"
#include "KerrEngineException.h"
using namespace std;

istream& operator>>(istream& in, Geometry& g1)
{
	throw KerrEngineException(EXCEPTION_NO_GEOMETRY_INPUT_REDIRECT);
	return in;
}
ostream& operator<<(ostream& out, const Geometry& g1)
{
	//cout << std::to_string(g1.type) << endl;
	//if (g1.type == VECTOR) { cout << "VECTOR ("; }
	//else if (g1.type == POINT) { cout << "POINT ("; }
	cout << "(" << std::to_string(g1.x) << ", " + std::to_string(g1.y) << ", " << std::to_string(g1.z) << ")";
	return out;
}

Geometry::Geometry()
{
	this->type = UNINITIALIZED_GEOMETRY;
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
	
}

Geometry::Geometry(const int& type, const double& x, const double& y, const double& z)
{
	this->type = type;
	this->x = x;
	this->y = y;
	this->z = z;
}

Geometry::~Geometry()
{

}

Geometry& Geometry::operator=(const Geometry& orig)
{
	this->type = orig.type;
	this->x = orig.x;
	this->y = orig.y;
	this->z = orig.z;
	return *this;
}

Geometry Geometry::operator+(const Geometry& g2) const
{
	Geometry g1 = *this;
	Geometry result;
	// check that geometry is initialized
	if (g1.type == UNINITIALIZED_GEOMETRY || g2.type == UNINITIALIZED_GEOMETRY) { throw KerrEngineException(EXCEPTION_UNINITIALIZED_GEOMETRY); }
	// point + point = not possible
	// 1 + 1 = 2
	else if (g1.type == POINT && g2.type == POINT) { throw KerrEngineException(EXCEPTION_ADDING_2_POINTS); }
	// vector + vector
	// 0 + 0 = 0
	else if (g1.type == VECTOR && g2.type == VECTOR) { result.vector((g1.x + g2.x), (g1.y + g2.y), (g1.z + g2.z)); }
	// point + vector (or vector + point) = point
	// 1 + 0 = 1
	// 0 + 1 = 1
	else if ((g1.type == POINT && g2.type == VECTOR) || (g1.type == VECTOR && g2.type == POINT)) { result.point((g1.x + g2.x), (g1.y + g2.y), (g1.z + g2.z)); }
	else { throw KerrEngineException(EXCEPTION_UNKNOWN_GEOMETRY); }
	return result;
}

Geometry Geometry::operator-(const Geometry& g2) const
{
	Geometry g1 = *this;
	Geometry result;
	// check that geometry is initialized
	if (g1.type == UNINITIALIZED_GEOMETRY || g2.type == UNINITIALIZED_GEOMETRY) { throw KerrEngineException(EXCEPTION_UNINITIALIZED_GEOMETRY); }
	// vector - point = not possible
	// 0 - 1 = -1
	else if (g1.type == VECTOR && g2.type == POINT) { throw KerrEngineException(EXCEPTION_SUBTRACT_POINT_FROM_VECTOR); }
	// point - vector = point
	// 1 - 0 = 1
	else if (g1.type == POINT && g2.type == VECTOR) { result.point((g1.x - g2.x), (g1.y - g2.y), (g1.z - g2.z)); }
	// point - point = vector
	// 1 - 1 = 0
	else if ((g1.type == POINT && g2.type == POINT) || (g1.type == VECTOR && g2.type == POINT)) { result.vector((g1.x - g2.x), (g1.y - g2.y), (g1.z - g2.z)); }
	// vector - vector = vector
	// 0 - 0 = 0
	else if (g1.type == VECTOR && g2.type == VECTOR) { result.vector((g1.x - g2.x), (g1.y - g2.y), (g1.z - g2.z)); }
	else { throw KerrEngineException(EXCEPTION_UNKNOWN_GEOMETRY); }
	return result;
}

Geometry Geometry::operator-() const
{
	Geometry g1 = *this;
	// check that geometry is initialized
	if (g1.type == UNINITIALIZED_GEOMETRY) { throw KerrEngineException(EXCEPTION_UNINITIALIZED_GEOMETRY); }
	if (g1.type != VECTOR && g1.type != POINT) { throw KerrEngineException(EXCEPTION_NEGATING_NOT_POINT_OR_VECTOR); }
	Geometry result(g1.type, g1.x * -1, g1.y * -1, g1.z * -1);
	return result;
}

Geometry Geometry::operator*(const double& scalar) const
{
	Geometry g1 = *this;
	// check that geometry is initialized
	if (g1.type == UNINITIALIZED_GEOMETRY) { throw KerrEngineException(EXCEPTION_UNINITIALIZED_GEOMETRY); }
	Geometry result(g1.type, g1.x * scalar, g1.y * scalar, g1.z * scalar);
	return result;
}

Geometry Geometry::operator/(const double& scalar) const
{
	Geometry g1 = *this;
	// check that geometry is initialized
	if (g1.type == UNINITIALIZED_GEOMETRY) { throw KerrEngineException(EXCEPTION_UNINITIALIZED_GEOMETRY); }
	Geometry result(g1.type, g1.x / scalar, g1.y / scalar, g1.z / scalar);
	return result;
}

void Geometry::vector(const double& x, const double& y, const double& z)
{
	this->type = VECTOR;
	this->x = x;
	this->y = y;
	this->z = z;
}

void Geometry::point(const double& x, const double& y, const double& z)
{
	this->type = POINT;
	this->x = x;
	this->y = y;
	this->z = z;
}

 Geometry Geometry::create(const int& type, const double& x, const double& y, const double& z)
{
	Geometry result(type, x, y, z);
	return result;
}

// Calculates the length of a vector.
double Geometry::magnitude(const Geometry& g1)
{
	// check that geometry is initialized
	if (g1.type == UNINITIALIZED_GEOMETRY) { throw KerrEngineException(EXCEPTION_UNINITIALIZED_GEOMETRY); }
	return sqrt(pow(g1.x, 2) + pow(g1.y, 2) + pow(g1.z, 2));
}

// Converts an arbitrary vector to the unit vector (length 1).
Geometry Geometry::normalize(const Geometry& g1)
{
	Geometry result;
	double magnitude;
	// check that geometry is initialized
	if (g1.type == UNINITIALIZED_GEOMETRY) { throw KerrEngineException(EXCEPTION_UNINITIALIZED_GEOMETRY); }
	// check that parameter is a vector
	if (g1.type != VECTOR) { throw KerrEngineException(EXCEPTION_DOT_PRODUCT_NOT_VECTORS); }
	magnitude = Geometry::magnitude(g1);
	result.vector(
		(g1.x / magnitude)
	  , (g1.y / magnitude)
	  , (g1.z / magnitude));
	return result;
}

// Takes two vectors and returns a scalar value (which is the cosine of the angle between them).
// Smaller dot product means larger angle between the vectors.
// Dot product of 1 = identical
// Dot product of -1 = opposite directions
double Geometry::dot(const Geometry& g1, const Geometry& g2)
{
	// Check that geometry is initialized
	if (g1.type == UNINITIALIZED_GEOMETRY || g2.type == UNINITIALIZED_GEOMETRY) { throw KerrEngineException(EXCEPTION_UNINITIALIZED_GEOMETRY); }
	// Check that both parameters are vectors
	if (g1.type != VECTOR || g2.type != VECTOR) { throw KerrEngineException(EXCEPTION_DOT_PRODUCT_NOT_VECTORS); }
	return (
		(g1.x * g2.x)
	  + (g1.y * g2.y)
	  + (g1.z * g2.z));
}

// Takes two vectors and returns a new vector that is perpindicular to the others.
Geometry Geometry::cross(const Geometry& g1, const Geometry& g2)
{
	// Check that geometry is initialized
	if (g1.type == UNINITIALIZED_GEOMETRY || g2.type == UNINITIALIZED_GEOMETRY) { throw KerrEngineException(EXCEPTION_UNINITIALIZED_GEOMETRY); }
	// Check that both are vectors
	if (g1.type != VECTOR || g2.type != VECTOR) { throw KerrEngineException(EXCEPTION_DOT_PRODUCT_NOT_VECTORS); }
	Geometry result(VECTOR,
		((g1.y * g2.z) - (g1.z * g2.y))
	  , ((g1.z * g2.x) - (g1.x * g2.z))
	  , ((g1.x * g2.y) - (g1.y * g2.x)));
	return result;
}