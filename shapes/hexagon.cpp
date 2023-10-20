// Matthew Kerr

#include "hexagon.h"

Sphere *hexagon_corner() {
    Sphere *corner = new Sphere();
    corner->_transform = translation(0.0, 0.0, -1.0) * scaling(0.25, 0.25, 0.25);
    corner->_material._color = black();
    corner->_material._reflective = 1.0;
    return corner;
}

Cylinder *hexagon_edge() {
    Cylinder *edge = new Cylinder();
    edge->_min = 0.0;
    edge->_max = 1.0;
    edge->_transform = translation(0.0, 0.0, -1.0)
                        * rotation_y(-PI_OVER_6)
                        * rotation_z(-PI_OVER_2)
                        * scaling(0.25, 1.0, 0.25);
    edge->_material._color = black();
    edge->_material._reflective = 1.0;
    return edge;
}

Group *hexagon_side() {
    Group *side = new Group();
    side->add_child(hexagon_corner());
    side->add_child(hexagon_edge());
    return side;
}

Group *hexagon() {
    Group *side = nullptr;
    Group *hex = new Group();
    for (int i = 0; i < 6; i++) {
        side = hexagon_side();
        side->_transform = rotation_y(i * PI_OVER_3);
        hex->add_child(side);
    }
    return hex;
}