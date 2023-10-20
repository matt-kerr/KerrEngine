#include "shape.h"

std::ostream& operator<<(std::ostream &out, const Shape &s) {
    std::cout << typeid(s).name() << " (Shape):" << std::endl
              << "  transform: " << std::endl << s._transform << std::endl
              << "  material: " << s._material << std::endl;
    return out;
}

Shape::Shape() { }

Intersections Shape::intersect(Ray ray) {
    Ray object_ray = transform_ray(ray, inverse(_transform));
    return local_intersect(object_ray);
}

Tuple Shape::normal_at(Tuple world_point) {
    Tuple local_point = world_to_object((Shape *)this, world_point);
    Tuple local_normal = local_normal_at(local_point);
    return normal_to_world((Shape *)this, local_normal);
}

BoundingBox Shape::parent_space_bounds() {
    BoundingBox temp = bounds();
    return temp.transform(_transform);
}

Tuple world_to_object(Shape *shape, Tuple point) {
    Tuple point2;
    if (shape->_parent != nullptr) { point2 = world_to_object(shape->_parent, point); }
    else { point2 = point; }
    return inverse(shape->_transform) * point2;
}

Tuple normal_to_world(Shape *shape, Tuple normal) {
    Tuple normal2 = transpose(inverse(shape->_transform)) * normal;
    normal2._w = 0.0;
    normal2 = normalize(normal2);
    if (shape->_parent != nullptr) { normal2 = normal_to_world(shape->_parent, normal2); }
    return normal2;
}