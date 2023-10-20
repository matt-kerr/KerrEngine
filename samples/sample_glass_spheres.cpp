// Matthew Kerr

#include "sample_glass_spheres.h"

void SampleGlassSpheres::run(int width, int height, std::string filepath) {
	std::ofstream fout(filepath);

    World world;
	world._light = new PointLight(create_point(2.0, 10.0, -5.0), Color(0.9, 0.9, 0.9));

	Shape* wall = new Plane();
	wall->_transform = translation(0.0, 0.0, 10.0) * rotation_x(1.5708);
	wall->_material._pattern = new CheckerPattern(Color(0.15, 0.15, 0.15), Color(0.85, 0.85, 0.85));
	wall->_material._ambient = 0.8;
	wall->_material._diffuse = 0.2;
	wall->_material._specular = 0.0;
	world._shapes.push_back(wall);

	Shape* glass_ball = new Sphere();
	glass_ball->_material._color = Color(1.0, 1.0, 1.0);
	glass_ball->_material._ambient = 0.0;
	glass_ball->_material._diffuse = 0.0;
	glass_ball->_material._specular = 0.9;
	glass_ball->_material._shininess = 300;
	glass_ball->_material._reflective = 0.9;
	glass_ball->_material._transparency = 0.9;
	glass_ball->_material._refractive_index = 1.5;
	world._shapes.push_back(glass_ball);

	Shape* hollow_center = new Sphere();
	hollow_center->_transform = scaling(0.5, 0.5, 0.5);
	hollow_center->_material._color = Color(1.0, 1.0, 1.0);
	hollow_center->_material._ambient = 0.0;
	hollow_center->_material._diffuse = 0.0;
	hollow_center->_material._specular = 0.9;
	hollow_center->_material._shininess = 300;
	hollow_center->_material._reflective = 0.9;
	hollow_center->_material._transparency = 0.9;
	hollow_center->_material._refractive_index = 1.0000034;
	world._shapes.push_back(hollow_center);

	Camera camera(width, height, 0.45);
	camera._transform = view_transform(create_point(0.0, 0.0, -5.0), create_point(0.0, 0.0, 0.0), create_vector(0.0, 1.0, 0.0));

	Canvas *c = camera.render(world);
	c->save_image(fout, 255);

	world.clear();
}
