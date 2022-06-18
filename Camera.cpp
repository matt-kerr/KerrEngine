// Matthew Kerr

#include "KerrEngineException.h"
#include "Camera.h"
#include "Matrix.h"
#include "Canvas.h"
#include "World.h"

Camera::Camera() { throw KerrEngineException("EXCEPTION_CANNOT_USE_CAMERA_DEFAULT_CONSTRUCTOR"); }

Camera::~Camera() { }

Camera::Camera(const int& hsize, const int& vsize, const double& field_of_view)
{
    double half_view = tan(field_of_view / 2.0);
    double aspect = (double)hsize / (double)vsize;
    this->hsize = hsize;
    this->vsize = vsize;
    this->field_of_view = field_of_view;
    this->transform = Matrix::identity(4);
    if (aspect >= 1.0)
    {
        this->half_width = half_view;
        this->half_height = half_view / aspect;
    }
    else
    {
        this->half_width = half_view * aspect;
        this->half_height = half_view;
    }
    this->pixel_size = (this->half_width * 2.0) / this->hsize;
}

Ray Camera::rayForPixel(const Camera& c, const double& px, const double& py)
{
    double xoffset = (px + 0.5) * c.pixel_size;
    double yoffset = (py + 0.5) * c.pixel_size;
    double world_x = c.half_width - xoffset;
    double world_y = c.half_height - yoffset;
    Matrix pixel = Matrix::inverse(c.transform) * Matrix::point(world_x, world_y, -1.0);
    Matrix origin = Matrix::inverse(c.transform) * Matrix::point(0.0, 0.0, 0.0);
    Matrix direction = Matrix::normalize(pixel - origin);
    return Ray(origin, direction);
}

Canvas Camera::render(const Camera& camera, const World& world)
{
    Canvas image(camera.hsize, camera.vsize);
    Ray ray;
    Color color;
    for (int y = 0; y < (camera.vsize - 1); y++)
    {
        for (int x = 0; x < (camera.hsize - 1); x++)
        {
            ray = Camera::rayForPixel(camera, x, y);
            color = World::colorAt(world, ray);
            image.writePixel(x, y, color);
        }
    }
    return image;
}