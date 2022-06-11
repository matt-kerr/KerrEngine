// Matthew Kerr

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <string>
using namespace std;

class Intersection
{
	public:
		double t;
		void *obj;
		string obj_type;
		
		Intersection();
		virtual ~Intersection();
		Intersection(double t, void* obj, std::string obj_type);
		static Intersection* intersections(int count, Intersection params ...);
		static Intersection hit(int count, Intersection* xs);
};

#endif;