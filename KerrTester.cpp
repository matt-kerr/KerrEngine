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
	// Putting it together
	string images_path = "C:\\KerrEngine_images\\";
	ofstream fout(images_path + "image.ppm");

	World world;

	Plane* floor = new Plane();
	floor->material.color = Color(0.6, 0.6, 0.6);
	floor->material.specular = 0.0;
	floor->material.pattern = Pattern(Color(0.2, 0.2, 0.2), Color(0.5, 0.5, 0.5), "checkers", Matrix::translation(5.0, 0.0, 0.0));

	Sphere* left = new Sphere();
	left->transform = Matrix::translation(-1.5, 0.33, -0.75) * Matrix::scaling(0.33, 0.33, 0.33);
	left->material.color = Color(0.8, 0.8, 0.8);
	left->material.diffuse = 0.7;
	left->material.specular = 0.3;
	left->material.pattern = Pattern(Color(0.3, 0.3, 0.3), Color(0.8, 0.8, 0.8), "ring", Matrix::scaling(0.03, 0.04, 0.05) * Matrix::rotationZ(std::numbers::pi / 3));

	Sphere* middle = new Sphere();
	middle->transform = Matrix::translation(-0.5, 1.0, 0.5);
	middle->material.color = Color(0.1, 0.5, 1.0);
	middle->material.diffuse = 0.7;
	middle->material.specular = 0.3;
	middle->material.pattern = Pattern(Color(0.0, 0.3, 0.8), Color(0.3, 0.8, 0.8), "stripe", Matrix::scaling(0.1, 0.1, 0.1) * Matrix::rotationZ(std::numbers::pi / 2));

	Sphere* right = new Sphere();
	right->transform = Matrix::translation(1.5, 0.5, -0.5) * Matrix::scaling(0.5, 0.5, 0.5);
	right->material.color = Color(0.1, 1.0, 0.5);
	right->material.diffuse = 0.7;
	right->material.specular = 0.3;
	right->material.pattern = Pattern(Color(0.9, 0.2, 0.2), Color(0.2, 0.9, 0.2), "gradient", Matrix::translation(1.0, 0.0, 0.0) * Matrix::scaling(2.0, 1.0, 1.0));

	world.shapes.push_back(floor);
	world.shapes.push_back(left);
	world.shapes.push_back(middle);
	world.shapes.push_back(right);

	Camera camera(800, 600, (std::numbers::pi / 3));
	camera.transform = Matrix::viewTransform(Matrix::point(0.0, 1.5, -5.0), Matrix::point(0.0, 1.0, 0.0), Matrix::vector(0.0, 1.0, 0.0));

	Canvas c = Camera::render(camera, world);
	c.saveImage(fout, 255);
	fout.close();

	world.shapes.clear();
	delete floor;
	delete left;
	delete middle;
	delete right;


	return 0;
}