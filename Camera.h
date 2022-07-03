// Matthew Kerr

#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix.h"
#include "Ray.h"
#include "Canvas.h"
#include "World.h"
#include "KerrMath.h"
#include "KerrEngineException.h"

class Camera
{
    public:
        int hsize;
        int vsize;
        double field_of_view;
        Matrix transform;
        double pixel_size;
        double half_width;
        double half_height;

        // constructors
        Camera();
        virtual ~Camera();
        Camera(const int& hsize, const int& vsize, const double& field_of_view);

        // camera functions
        static Ray rayForPixel(const Camera& camera, const double& px, const double& py);
        static Canvas render(const Camera& camera, const World& world);
};

#endif