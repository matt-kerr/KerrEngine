// Matthew Kerr

#include "world.h"

World::World() { }

void World::add_shape(Shape *obj) {
	_shapes.push_back(obj);
}
void World::clear() {
	if (_light != nullptr) { delete _light; }
	for (int i = 0; i < _shapes.size(); i++) {
		delete _shapes[i];
	}
	_shapes.clear();
}

World default_world() {
	World w;
	w._light = new PointLight(create_point(-10.0, 10.0, -10.0), Color(1.0, 1.0, 1.0));
	Sphere *s1 = new Sphere();
	Sphere *s2 = new Sphere();
	s1->_material._color = Color(0.8, 1.0, 0.6);
	s1->_material._diffuse = 0.7;
	s1->_material._specular = 0.2;
	s2->_transform = scaling(0.5, 0.5, 0.5);
	w.add_shape(s1);
	w.add_shape(s2);
	return w;
}

Intersections intersect_world(const World& w, const Ray& r) {
	Intersections xs, curr;
	for (int i = 0; i < w._shapes.size(); i++) {
		curr = w._shapes[i]->intersect(r);
		if (curr.count() > 0) { xs.merge(curr); }
	}
	return xs;
}

Color color_at(World w, Ray r, int remaining) {
	Intersections xs = intersect_world(w, r);
	if (xs.count() == 0) { return black(); }
	Intersection h = hit(xs);
	if (h._t <= 0.0) { return black(); }
	PreparedComputation comps(h, r, xs);
	return shade_hit(w, comps, remaining);
}

bool is_shadowed(const World& w, const Tuple& point) {
	Tuple v = w._light->_position - point;
	double distance = magnitude(v);
	Tuple direction = normalize(v);
	Ray r(point, direction);
	Intersections xs = intersect_world(w, r);
	Intersection h = hit(xs);
	return h._obj != nullptr && h._t < distance;
}

Color shade_hit(World w, PreparedComputation comps, int remaining) {
	bool in_shadow = is_shadowed(w, comps._over_point);
	Color surface = lighting(comps._obj->_material, comps._obj, w._light, comps._over_point, comps._eyev, comps._normalv, in_shadow);
	Color reflected = reflected_color(w, comps, remaining);
	Color refracted = refracted_color(w, comps, remaining);
	if (comps._obj->_material._reflective > 0.0 && comps._obj->_material._transparency > 0.0) {
		double reflectance = schlick(comps);
		return surface + reflected * reflectance + refracted * (1.0 - reflectance);
	}
	return surface + reflected + refracted;
}

Color lighting(const Material &material, Shape *object, Light *light, const Tuple &point, const Tuple &eyev, const Tuple &normalv, const bool& in_shadow) {
	Color color;
	if (material._pattern != nullptr && (*material._pattern)._active) { color = pattern_at_object(material._pattern, object, point); }
	else { color = material._color; }
	Color effective_color = color * light->_intensity;
	Color ambient = effective_color * material._ambient;
	if (in_shadow)  { return ambient; }
	Color diffuse;
	Color specular;
	Tuple lightv = normalize(light->_position - point);
	double light_dot_normal = dot(lightv, normalv);
	if (light_dot_normal < 0.0) {
		diffuse = black();
		specular = black();
	} else {
		diffuse = effective_color * material._diffuse * light_dot_normal;
		Tuple reflectv = reflect(-lightv, normalv);
		double reflect_dot_eye = dot(reflectv, eyev);
		if (reflect_dot_eye <= 0.0) { specular = black(); }
		else {
			double factor = std::pow(reflect_dot_eye, material._shininess);
			specular = light->_intensity * material._specular * factor;
		}
	}
	return ambient + diffuse + specular;
}

Color pattern_at_object(Pattern *pattern, Shape *object, Tuple world_point) {
	Tuple object_point = inverse(object->_transform) * world_point;
    Tuple pattern_point = inverse(pattern->_transform) * object_point;
	return pattern->pattern_at(pattern_point);
}

Color reflected_color(World world, PreparedComputation comps, int remaining)
{
	if (remaining <= 0 || comps._obj->_material._reflective == 0.0) { return black(); }
	Ray reflect_ray(comps._over_point, comps._reflectv);
	Color color = color_at(world, reflect_ray, remaining - 1);
	return color * (*comps._obj)._material._reflective;
}

Color refracted_color(World world, PreparedComputation comps, int remaining)
{
	if (remaining == 0) { return Color(0.0, 0.0, 0.0); }
	if (comps._obj->_material._transparency == 0.0) { return Color(0.0, 0.0, 0.0); }
	double n_ratio = comps._n1 / comps._n2;
	double cos_i = dot(comps._eyev, comps._normalv);
	double sin2_t = std::pow(n_ratio, 2.0) * (1.0 - std::pow(cos_i, 2.0));
	if (sin2_t > 1.0) { return Color(0.0, 0.0, 0.0); }
	double cos_t = std::sqrt(1.0 - sin2_t);
	Tuple direction = comps._normalv * (n_ratio * cos_i - cos_t) - comps._eyev * n_ratio;
	Ray refract_ray(comps._under_point, direction);
	return color_at(world, refract_ray, remaining - 1) * comps._obj->_material._transparency;
}

double schlick(PreparedComputation comps) {
	double cos = dot(comps._eyev, comps._normalv);
	if (comps._n1 > comps._n2) {
		double n = comps._n1 / comps._n2;
		double sin2_t = std::pow(n, 2.0) * (1.0 - std::pow(cos, 2.0));
		if (sin2_t > 1.0) { return 1.0; }
		cos = std::sqrt(1.0 - sin2_t);
	}
	double r0 = std::pow(((comps._n1 - comps._n2) / (comps._n1 + comps._n2)), 2.0);
	return r0 + (1.0 - r0) * std::pow((1.0 - cos), 5.0);
}