// Matthew Kerr

#include "camera.h"

Camera::Camera(const int& width, const int& height, const double& field_of_view) {
    double half_view = std::tan(field_of_view / 2.0);
    double aspect = (double)width / (double)height;
    _width = width;
    _height = height;
    _field_of_view = field_of_view;
    _transform = identity_matrix(4);
    if (aspect >= 1.0) {
        _half_width = half_view;
        _half_height = half_view / aspect;
    }
    else {
        _half_width = half_view * aspect;
        _half_height = half_view;
    }
    _pixel_size = _half_width * 2.0 / _width;
}

Ray Camera::ray_for_pixel(const double& px, const double& py) {
	double xoffset = (px + 0.5) * _pixel_size;
	double yoffset = (py + 0.5) * _pixel_size;
	double world_x = _half_width - xoffset;
	double world_y = _half_height - yoffset;
	Tuple pixel = inverse(_transform) * create_point(world_x, world_y, -1.0);
	Tuple origin = inverse(_transform) * create_point(0.0, 0.0, 0.0);
	Tuple direction = normalize(pixel - origin);
	return Ray(origin, direction);
}

Canvas *Camera::render(const World& world) {
	std::cout << "hardware supports " << std::thread::hardware_concurrency() << " threads" << std::endl;
	std::vector<std::thread> threads;
	Canvas *canvas = new Canvas(_width, _height);
	for (unsigned i = 0; i < std::thread::hardware_concurrency(); i++) {
		std::thread thread (&Camera::render_thread, this, canvas, world, i);
		threads.push_back(std::move(thread));
	}
	for (unsigned i = 0; i < threads.size(); i++) {
		threads[i].join();
	}
	//for (int y = 0; y < _height; y++) {
	//	if (VERBOSE_CAMERA) { std::cout <<"rendering row " << y + 1 << "/" << _height << std::endl; }
	//	for (int x = 0; x < _width; x++) {
	//		image.write_pixel(x, y, color_at(world, ray_for_pixel((double)x, (double)y), 5));
	//	}
	//}
	std::cout << "done" << std::endl;
	return canvas;
}

void Camera::render_thread(Canvas *canvas, World world, int offset) {
	for (unsigned y = 0; y < (unsigned)_height; y++) {
		if (y % std::thread::hardware_concurrency() != offset) { continue; }
		//std::string msg = "thread ";
		//msg += std::to_string(offset);
		//msg += " rendering row ";
		//msg += std::to_string(y);
		//msg += '\n';// + std::endl;
		//std::cout << msg;
		for (int x = 0; x < _width; x++) {
			Color c = color_at(world, ray_for_pixel((double)x, (double)y), REFLECTION_DEPTH);
			canvas->write_pixel(x, y, c);
		}
	}
}