// Matthew Kerr

#include "glass_sphere.h"

GlassSphere::GlassSphere() : Sphere() {
    _material._transparency = 1.0;
    _material._refractive_index = 1.5;
}
