// Matthew Kerr

#ifndef KERR_ENGINE_H
#define KERR_ENGINE_H

#include "kerr_inline.h"
#include "kerr_math.h"

#include "lights/light.h"
#include "lights/point_light.h"

#include "patterns/pattern.h"
#include "patterns/stripe_pattern.h"
#include "patterns/gradient_pattern.h"
#include "patterns/ring_pattern.h"
#include "patterns/checker_pattern.h"
#include "patterns/test_pattern.h"

#include "primitives/color.h"
#include "primitives/intersection.h"
#include "primitives/intersections.h"
#include "primitives/matrix.h"
#include "primitives/ray.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"

#include "scene/camera.h"
#include "scene/canvas.h"
#include "scene/prepared_computation.h"
#include "scene/world.h"

#include "shapes/material.h"
#include "shapes/shape.h"
#include "shapes/sphere.h"
#include "shapes/glass_sphere.h"
#include "shapes/plane.h"
#include "shapes/cube.h"
#include "shapes/cylinder.h"
#include "shapes/cone.h"
#include "shapes/group.h"
#include "shapes/bounding_box.h"
#include "shapes/hexagon.h"
#include "shapes/triangle.h"
#include "shapes/obj_parser.h"

#endif