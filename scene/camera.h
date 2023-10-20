// Matthew Kerr

#ifndef CAMERA_H
#define CAMERA_H

#include <thread>
//#include <vector>
#include "../kerr_inline.h"
#include "../primitives/matrix.h"
#include "../primitives/ray.h"
#include "canvas.h"
#include "world.h"

class Canvas;
class Matrix;
class Ray;
class World;
class Camera
{
    public:
        int _width;
        int _height;
        double _field_of_view;
        double _pixel_size;
        double _half_width;
        double _half_height;
        Matrix _transform;

        Camera() { throw std::invalid_argument("Camera requires arguments"); }
        Camera(const int& width, const int& height, const double& field_of_view);
        virtual ~Camera() = default;

        Ray ray_for_pixel(const double& px, const double& py);
        Canvas *render(const World& world);
        void render_thread(Canvas *canvas, World world, int offset);
};

#endif