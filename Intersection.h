// Matthew Kerr

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <string>
#include <vector>
using namespace std;

class Intersection
{
	public:
		double t;
		void* obj;
		string obj_type;
		
		Intersection();
		virtual ~Intersection();
		Intersection(double t, void* obj, std::string obj_type);
		bool operator==(const Intersection& rhs); // == operator overload
		bool operator<(const Intersection& rhs); // < operator overload
		bool operator>(const Intersection& rhs); // > operator overload
		static std::vector<Intersection> intersections(int count, Intersection params ...);
		static std::vector<Intersection> intersections(int count, std::vector<Intersection> params ...);
		static Intersection hit(std::vector<Intersection> xs);
};

#endif;