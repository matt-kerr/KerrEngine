// Matthew Kerr

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "KerrEngine.h"
#include "World.h"
#include "Matrix.h"
#include "Shape.h"
#include "Sphere.h"
#include "Plane.h"
#include "Color.h"
#include "Camera.h"
#include "Canvas.h"
#include "Pattern.h"
using namespace std;

int main()
{
	string images_path = "C:\\KerrEngine_images\\";
	ofstream fout(images_path + "image.ppm");

	World world;
	world.light = PointLight(Matrix::point(-10.0, 10.0, -10.0), Color(1.0, 1.0, 1.0));

	Plane* floor = new Plane();
	floor->material.specular = 0.0;
	floor->material.reflective = 0.8;
	floor->material.pattern = Pattern(Color(0.2, 0.2, 0.2), Color(0.5, 0.5, 0.5), "stripe", Matrix::scaling(0.1, 0.1, 0.1));

	Plane* wall = new Plane();
	wall->transform = Matrix::translation(0.0, 0.0, 5.0) * Matrix::rotationX(std::numbers::pi / 2);
	wall->material.specular = 0.0;
	wall->material.pattern = Pattern(Color(0.215, 0.305, 0.451), Color(0.082, 0.133, 0.219), "checkers", Matrix::scaling(0.25, 0.25, 0.25) * Matrix::translation(0.5, 0.0, 0.0));

	Sphere* left = new Sphere();
	left->transform = Matrix::translation(-1.5, 0.33, -0.75) * Matrix::scaling(0.33, 0.33, 0.33);
	left->material.diffuse = 0.7;
	left->material.specular = 0.3;
	left->material.pattern = Pattern(Color(0.1, 0.1, 0.1), Color(0.6, 0.6, 0.6), "ring", Matrix::scaling(0.03, 0.04, 0.08) * Matrix::rotationZ(std::numbers::pi / 3));

	Sphere* middle = new Sphere();
	middle->transform = Matrix::translation(-0.5, 1.0, 0.5);
	middle->material.diffuse = 0.7;
	middle->material.specular = 0.3;
	middle->material.pattern = Pattern(Color(0.1, 0.4, 0.9), Color(0.3, 0.2, 0.9), "stripe", Matrix::scaling(0.1, 0.1, 0.1) * Matrix::rotationZ(std::numbers::pi / 2));

	Sphere* right = new Sphere();
	right->transform = Matrix::translation(1.5, 0.5, -0.5) * Matrix::scaling(0.5, 0.5, 0.5);
	right->material.diffuse = 0.7;
	right->material.specular = 0.3;
	right->material.pattern = Pattern(Color(0.9, 0.2, 0.2), Color(0.2, 0.9, 0.2), "gradient", Matrix::translation(1.0, 0.0, 0.0) * Matrix::scaling(2.0, 1.0, 1.0));

	world.shapes.push_back(floor);
	world.shapes.push_back(wall);
	world.shapes.push_back(left);
	world.shapes.push_back(middle);
	world.shapes.push_back(right);

	Camera camera(800, 600, PI_OVER_3);
	camera.transform = Matrix::viewTransform(Matrix::point(0.0, 1.5, -5.0), Matrix::point(0.0, 1.0, 0.0), Matrix::vector(0.0, 1.0, 0.0));

	Canvas c = Camera::render(camera, world);
	c.saveImage(fout, 255);
	fout.close();
	
	return 0;
}