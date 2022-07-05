// Matthew Kerr

#ifndef KERRMATH_H
#define KERRMATH_H

#include <vector>
#include <algorithm>
#include "Color.h"
#include "Matrix.h"
#include "Computations.h"
#include "Intersection.h"
#include "Ray.h"
#include "PointLight.h"
#include "World.h"
#include "Shape.h"
#include "Sphere.h"
#include "Pattern.h"
#include "KerrEngineException.h"

class KerrMath
{
    public:
        static Computations prepareComputations(Intersection intersection, Ray ray, std::vector<Intersection> xs);
        static Color lighting(const Material& material, Shape* object, const PointLight& light, const Matrix& point, const Matrix& eyev, const Matrix& normalv, const bool& in_shadow);
        static Matrix position(const Ray& r, const double& t);
        static Ray transform(const Ray& r, const Matrix& m);
        static std::vector<Intersection> intersectWorld(const World& w, const Ray& r);
        static std::vector<Intersection> localIntersectSphere(Shape* shape, const Ray& ray);
        static std::vector<Intersection> localIntersectPlane(Shape* shape, const Ray& ray);
        static Matrix normalAt(Shape* shape, const Matrix& point);
        static Matrix localNormalAtSphere(Shape* shape, const Matrix& world_point);
        static Matrix localNormalAtPlane(Shape* shape, const Matrix& world_point);
        static Color shadeHit(const World& world, const Computations& comps, const int& remaining);
        static bool isShadowed(const World& world, const Matrix& point);
        static Color colorAt(const World& world, const Ray& ray, const int& remaining);
        static Color reflectedColor(const World& world, const Computations& comps, const int& remaining);
        static Color patternAt(const Pattern& pattern, const Matrix& point);
        static Color patternAtShape(const Pattern& pattern, Shape* object, const Matrix& world_point);
};      

#endif