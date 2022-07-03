// Matthew Kerr

#include "Camera.h"

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

Ray Camera::rayForPixel(const Camera& camera, const double& px, const double& py)
{
	double xoffset = (px + 0.5) * camera.pixel_size;
	double yoffset = (py + 0.5) * camera.pixel_size;
	double world_x = camera.half_width - xoffset;
	double world_y = camera.half_height - yoffset;
	Matrix pixel = Matrix::inverse(camera.transform) * Matrix::point(world_x, world_y, -1.0);
	Matrix origin = Matrix::inverse(camera.transform) * Matrix::point(0.0, 0.0, 0.0);
	Matrix direction = Matrix::normalize(pixel - origin);
	return Ray(origin, direction);
}

Canvas Camera::render(const Camera& camera, const World& world)
{
	if (DEBUG)
	{
		cout << "entered Camera::render" << endl;
		cout << "world.shapes[0].type = " << world.shapes[0]->type << endl;
		cout << "world.shapes[0].transform = " << world.shapes[0]->transform << endl;
	}
	Canvas image(camera.hsize, camera.vsize);
	Ray ray;
	Color color;
	for (int y = 0; y < (camera.vsize - 1); y++)
	{
		cout << y + 1 << "/" << camera.vsize << endl;
		for (int x = 0; x < (camera.hsize - 1); x++)
		{
			ray = Camera::rayForPixel(camera, x, y);
			color = KerrMath::colorAt(world, ray);
			image.writePixel(x, y, color);
		}
	}
	return image;
}