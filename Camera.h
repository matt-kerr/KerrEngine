// Matthew Kerr

#ifndef CAMERA_H
#define CAMERA_H

#include <thread>
#include <vector>
#include "Matrix.h"
#include "Ray.h"
#include "Canvas.h"
#include "World.h"
#include "KerrMath.h"
#include "KerrEngine.h"
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

        static Canvas renderMultithreaded(const Camera& camera, const World& world, int num_threads);
        static void setCanvasColorMultithreaded(const Camera& camera, const World& world, Canvas image, const double& y_from, const double& y_to);
};

#endif