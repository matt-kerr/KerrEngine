// Matthew Kerr

#include <fstream>
#include <iostream>
#include <string>
#include "Matrix.h"
#include "Color.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Ray.h"
#include "Sphere.h"
#include "Intersection.h"
#include "PointLight.h"
#include "Material.h"
using namespace std;

int main()
{
	string images_path = "C:\\KerrEngine_images\\";
	ofstream fout(images_path + "image.ppm");
	int canvas_size = 500;
	Canvas c(canvas_size, canvas_size);
	Color blue(0.0, 0.0, 1.0);
	Material m;
	m.color = Color::create(0.2, 0.2, 1.0);
	Sphere s(1.0);
	s.material = m;
	Sphere* s_ptr = &s;
	Matrix light_position = Matrix::createPoint(-10.0, 10.0, -10.0);
	Matrix point, normal, eye;
	Color light_color(1.0, 1.0, 1.0);
	PointLight light(light_position, light_color);
	Matrix ray_origin, position;
	Ray r;
	ray_origin.point(0.0, 0.0, -5.0);
	r.origin = ray_origin;
	double wall_z = 10.0;
	double wall_size = 7.0;
	double pixel_size = wall_size / canvas_size;
	double half = wall_size / 2.0;
	double world_y, world_x;
	for (int y = 0; y < (canvas_size - 1); y++)
	{
		world_y = half - (pixel_size * y);
		for (int x = 0; x < (canvas_size - 1); x++)
		{
			world_x = (-1.0 * half) + (pixel_size * x);
			position.point(world_x, world_y, wall_z);
			Matrix normalized = (position - ray_origin).normalize();
			r.direction = normalized;
			Intersection* xs = r.intersectSphere(s_ptr);
			Intersection hit = Intersection::hit(2, xs);
			if (hit.t >= 0)
			{
				point = r.position(hit.t);
				normal = (*(Sphere*)hit.obj).normalAt(point);
				eye = r.direction * -1.0;
				c.writePixel(x, y, (*(Sphere*)hit.obj).material.lighting(light, point, eye, normal));
			}
		}
	}
	c.saveImage(fout, 255);
	fout.close();

	return 0;
}