// Matthew Kerr

#include "sample_teddy.h"

// translation(+right/-left/ +up/-down, +further/-closer)
// scaling (width, height, depth)
void SampleTeddy::run(int width, int height, std::string filepath) {
    std::ofstream fout(filepath);

    World world;
    world._light = (Light *)new PointLight(create_point(-5.0, 20.0, -15.0), Color(1.0, 1.0, 1.0));

    Plane *floor = new Plane();
    floor->_transform = translation(0.0, -20.0, 0.0);
    floor->_material._specular = 0.9;
    floor->_material._reflective = 0.3;
    floor->_material._pattern = (Pattern *)new RingPattern(Color(0.4, 0.4, 0.4), Color(0.5, 0.5, 0.5), scaling(1.0, 1.0, 1.0));
    world._shapes.push_back(floor);

    Plane *wall = new Plane();
    wall->_transform = translation(0.0, 0.0, 100.0) * rotation_x(PI_OVER_2);
    wall->_material._specular = 0.3;
    wall->_material._reflective = 0.3;
    wall->_material._color = Color(0.215, 0.305, 0.451);
    world._shapes.push_back(wall);

    std::ifstream fin("samples/teddy.obj");
    OBJ_Parser parser = parse_obj_file(fin);
    Group *g = parser._default_group;
    g->_transform = translation(0.0, 12.0, 25.0) * rotation_y(PI);
    cout << "triangles before divide = " << g->_shapes.size() << std::endl;
    g->divide(1);
    cout << "groups after divide = " << g->_shapes.size() << std::endl;
    
    world._shapes.push_back(g);

    std::cout << "bad lines = " << parser._bad_lines << std::endl;

    Camera camera(width, height, PI_OVER_3);
    camera._transform = view_transform(create_point(0.0, 10.0, -25.0), create_point(0.0, 10, 0.0), create_vector(0.0, 1.0, 0.0));

    Canvas *c = camera.render(world);
	c->save_image(fout, 255);

    fout.close();
    world.clear();
}
