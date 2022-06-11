// Matthew Kerr
#ifndef GEOMETRY_H
#define GEOMETRY_H
#define UNINITIALIZED_GEOMETRY -1
#define EPSILON 0.00001
#define VECTOR 0
#define POINT 1

#include <iostream>
#include "KerrEngine.h"
using namespace std;

class Geometry
{
	friend istream& operator>>(istream& in, Geometry& g1);
	friend ostream& operator<<(ostream& out, const Geometry& g1);

	public:
		int type;
		double x;
		double y;
		double z;
		Geometry();
		Geometry(const int& type, const double& x, const double& y, const double& z);
		virtual ~Geometry();
		Geometry& operator=(const Geometry& g2);
		Geometry operator+(const Geometry& g2) const;
		Geometry operator-(const Geometry& g2) const;
		Geometry operator-() const;
		Geometry operator*(const double& scalar) const;
		Geometry operator/(const double& scalar) const;
		void vector(const double& x, const double& y, const double& z);
		void point(const double& x, const double& y, const double& z);
		static Geometry create(const int& type, const double& x, const double& y, const double& z);
		static double magnitude(const Geometry& g1);
		static Geometry normalize(const Geometry& g1);
		static double dot(const Geometry& g1, const Geometry& g2);
		static Geometry cross(const Geometry& g1, const Geometry& g2);
};

#endif
