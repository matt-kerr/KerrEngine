// Matthew Kerr

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "KerrEngine.h"
#include "Matrix.h"
#include "Color.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Ray.h"
#include "Sphere.h"
#include "Intersection.h"
#include "PointLight.h"
#include "Material.h"
#include "World.h"
#include "Computations.h"
#include "Camera.h"
using namespace std;

int main()
{	
	// Putting it together
	string images_path = "C:\\KerrEngine_images\\";
	ofstream fout(images_path + "image.ppm");

	World world;
	Sphere floor;
	floor.transform = Matrix::scaling(10.0, 0.01, 10.0);
	floor.material.color = Color::create(1.0, 0.9, 0.9);
	floor.material.specular = 0.0;

	Sphere left_wall;
	left_wall.transform = Matrix::translation(0.0, 0.0, 5.0)
		* Matrix::rotationY(-(std::numbers::pi / 4))
		* Matrix::rotationX(std::numbers::pi / 2)
		* Matrix::scaling(10.0, 0.01, 10.0);

	Sphere right_wall;
	right_wall.transform = Matrix::translation(0.0, 0.0, 5.0)
		* Matrix::rotationY(std::numbers::pi / 4)
		* Matrix::rotationX(std::numbers::pi / 2)
		* Matrix::scaling(10.0, 0.01, 10.0);

	Sphere middle;
	middle.transform = Matrix::translation(-0.5, 1.0, 0.5);
	middle.material.color = Color::create(0.1, 0.5, 1.0);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;

	Sphere right;
	right.transform = Matrix::translation(1.5, 0.5, -0.5) * Matrix::scaling(0.5, 0.5, 0.5);
	right.material.color = Color::create(0.1, 1.0, 0.5);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;

	Sphere left;
	left.transform = Matrix::translation(-1.5, 0.33, -0.75) * Matrix::scaling(0.33, 0.33, 0.33);
	left.material.color = Color::create(0.8, 0.8, 0.8);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;

	world.spheres.push_back(floor);
	world.spheres.push_back(left_wall);
	world.spheres.push_back(right_wall);
	world.spheres.push_back(middle);
	world.spheres.push_back(right);
	world.spheres.push_back(left);

	Camera camera(80, 60, (std::numbers::pi / 3));
	camera.transform = Matrix::viewTransform(Matrix::point(0.0, 1.5, -5.0), Matrix::point(0.0, 1.0, 0.0), Matrix::vector(0.0, 1.0, 0.0));

	Canvas c = Camera::render(camera, world);
	c.saveImage(fout, 255);
	fout.close();

	return 0;
}