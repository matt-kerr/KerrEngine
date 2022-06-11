// Matthew Kerr

#include <fstream>
#include <iostream>
#include <string>
#include "Geometry.h"
#include "Environment.h"
#include "Projectile.h"
#include "Color.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Ray.h"
#include "Sphere.h"
#include "Intersection.h"
using namespace std;

int main()
{
	string images_path = "C:\\KerrEngine_images\\";
	ofstream fout(images_path + "image.ppm");
	int canvas_size = 100;
	Canvas c(canvas_size, canvas_size);
	Color blue(0.0, 0.0, 1.0);
	Sphere s(1.0);
	Sphere * s_ptr = &s;
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
			Matrix normalized = position - ray_origin;
			r.direction = normalized;
			Intersection* xs = r.intersectSphere(s_ptr);
			Intersection hit = Intersection::hit(2, xs);
			if (hit.t >= 0)
			{
				c.writePixel(x, y, blue);
			}
		}
	}
	c.saveImage(fout, 255);
	fout.close();

	return 0;
}