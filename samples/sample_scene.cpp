// Matthew Kerr

#include "sample_scene.h"

void SampleScene::run(int width, int height, std::string filepath) {
    std::ofstream fout(filepath);

    World world;
    world._light = (Light *)new PointLight(create_point(-10.0, 10.0, -10.0), Color(1.0, 1.0, 1.0));

    Plane* floor = new Plane();
    floor->_material._specular = 0.0;
    floor->_material._reflective = 0.8;
    floor->_material._pattern = (Pattern *)new StripePattern(Color(0.2, 0.2, 0.2), Color(0.5, 0.5, 0.5), scaling(0.1, 0.1, 0.1));

    Plane* wall = new Plane();
    wall->_transform = translation(0.0, 0.0, 5.0) * rotation_x(PI_OVER_2);
    wall->_material._specular = 0.0;
    wall->_material._pattern = (Pattern *)new CheckerPattern(Color(0.215, 0.305, 0.451), Color(0.082, 0.133, 0.219), scaling(0.25, 0.25, 0.25) * translation(0.5, 0.0, 0.0));

    Sphere* left = new Sphere();
    left->_transform = translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33);
    left->_material._diffuse = 0.7;
    left->_material._specular = 0.3;
    left->_material._pattern = (Pattern *)new RingPattern(Color(0.1, 0.1, 0.1), Color(0.6, 0.6, 0.6), scaling(0.03, 0.04, 0.08) * rotation_z(PI_OVER_3));

    Sphere* middle = new Sphere();
    middle->_transform = translation(-0.5, 1.0, 0.5);
    middle->_material._diffuse = 0.7;
    middle->_material._specular = 0.3;
    middle->_material._pattern = (Pattern *)new StripePattern(Color(0.1, 0.4, 0.9), Color(0.3, 0.2, 0.9), scaling(0.1, 0.1, 0.1) * rotation_z(PI_OVER_2));

    Sphere* right = new Sphere();
    right->_transform = translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5);
    right->_material._diffuse = 0.7;
    right->_material._specular = 0.3;
    right->_material._pattern = (Pattern *)new GradientPattern(Color(0.9, 0.2, 0.2), Color(0.2, 0.9, 0.2), translation(0.99, 0.0, 0.0) * scaling(2.0, 1.0, 1.0));

    world._shapes.push_back(floor);
    world._shapes.push_back(wall);
    world._shapes.push_back(left);
    world._shapes.push_back(middle);
    world._shapes.push_back(right);

    Camera camera(width, height, PI_OVER_3);
    camera._transform = view_transform(create_point(0.0, 1.5, -5.0), create_point(0.0, 1.0, 0.0), create_vector(0.0, 1.0, 0.0));

    Canvas *c = camera.render(world);
	c->save_image(fout, 255);

    delete c;
    fout.close();
    world.clear();
}
