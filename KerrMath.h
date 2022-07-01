// Matthew Kerr

#ifndef KERRMATH_H
#define KERRMATH_H

#include "Color.h"
#include "Matrix.h"
#include "Computations.h"
#include "Intersection.h"
#include "Ray.h"
#include "PointLight.h"
#include "World.h"
#include "Shape.h"
#include "Sphere.h"
#include "KerrEngineException.h"

class KerrMath
{
    public:
        static Computations prepareComputations(Intersection intersection, Ray ray);
        static Color lighting(const Material& material, const PointLight& light, const Matrix& point, const Matrix& eyev, const Matrix& normalv, const bool& in_shadow);
        static Matrix position(const Ray& r, const double& t);
        static Ray transform(const Ray& r, const Matrix& m);
        static std::vector<Intersection> intersectWorld(const World& w, const Ray& r);
        static std::vector<Intersection> localIntersectSphere(Shape* shape, const Ray& ray);
        static std::vector<Intersection> localIntersectPlane(Shape* shape, const Ray& ray);
        static Matrix normalAt(Shape* shape, const Matrix& point);
        static Matrix localNormalAtSphere(Shape* sphere, const Matrix& world_point); // returns a Vector, takes a Point
        static Matrix localNormalAtPlane(Shape* plane, const Matrix& world_point);
        static Color shadeHit(const World& world, const Computations& comps);
        static Color colorAt(const World& world, const Ray& ray);
        static bool isShadowed(const World& world, const Matrix& point);
};

#endif