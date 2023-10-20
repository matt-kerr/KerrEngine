// Matthew Kerr

#ifndef HEXAGON_H
#define HEXAGON_H

#include "../primitives/transformation.h"
#include "shape.h"
#include "sphere.h"
#include "cylinder.h"
#include "group.h"
#include "bounding_box.h"

class Shape;
class Sphere;
class Cylinder;
class Group;
class BoundingBox;

Sphere *hexagon_corner();
Cylinder *hexagon_edge();
Group *hexagon_side();
Group *hexagon();

#endif


