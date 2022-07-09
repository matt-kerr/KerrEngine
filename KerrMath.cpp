#include "KerrMath.h"

Computations KerrMath::prepareComputations(Intersection intersection, Ray ray, std::vector<Intersection> xs)
{
	if (intersection.obj->type == "NONE") { throw KerrEngineException("EXCEPTION KERRMATH_PREPARECOMPUTATIONS_UNINITIALIZED_SHAPE"); }
	Matrix point = KerrMath::position(ray, intersection.t);
	Matrix eyev = -ray.direction;
	Matrix normalv = KerrMath::normalAt(intersection.obj, point);
	bool inside = false;
	if (Matrix::dot(normalv, eyev) < 0.0) { inside = true; normalv = -normalv; }
	else { inside = false; }
	Matrix reflectv = Matrix::reflect(ray.direction, normalv);
	Matrix over_point = point + normalv * EPSILON;
	Matrix under_point = point - normalv * EPSILON;
	std::vector<Shape*> containers;
	double n1 = -1.0;
	double n2 = -1.0;
	for (int i = 0; i < xs.size(); i++)
	{
		if (xs[i] == intersection)
		{
			if (containers.size() == 0) { n1 = 1.0; }
			else { n1 = containers.back()->material.refractive_index; }
		}
		int remove_index = -1;
		for (int j = 0; j < containers.size(); j++)
		{
			if (containers[j] == xs[i].obj) { remove_index = j; break; }
		}
		if (remove_index > -1) { containers.erase(containers.begin() + remove_index); }
		else { containers.push_back(xs[i].obj); }
		if (xs[i] == intersection)
		{
			if (containers.size() == 0) { n2 = 1.0; }
			else { n2 = containers.back()->material.refractive_index; }
			break;
		}
	}
	return Computations(intersection.t, intersection.obj, point, over_point, under_point, eyev, normalv, reflectv, inside, n1, n2);
}

Color KerrMath::lighting(const Material& material, Shape* object, const PointLight& light, const Matrix& point, const Matrix& eyev, const Matrix& normalv, const bool& in_shadow)
{
	Color color;
	if (material.pattern.type != "none") { color = KerrMath::patternAtShape(material.pattern, object, point); }
	else { color = material.color; }
	Color black(0.0, 0.0, 0.0);
	Color effective_color = color * light.intensity;
	Matrix lightv = Matrix::normalize(light.position - point);
	Color cont_ambient = effective_color * material.ambient;
	if (in_shadow) { return cont_ambient; }
	Color cont_diffuse;
	Color cont_specular;
	double light_dot_normal = Matrix::dot(lightv, normalv);
	double reflect_dot_eye, factor;
	if (light_dot_normal < 0.0)
	{
		cont_diffuse = black;
		cont_specular = black;
	}
	else
	{
		cont_diffuse = effective_color * material.diffuse * light_dot_normal;
		Matrix reflectv = Matrix::reflect(-lightv, normalv);
		reflect_dot_eye = Matrix::dot(reflectv, eyev);
		if (reflect_dot_eye <= 0.0)
		{
			cont_specular = black;
		}
		else
		{
			factor = pow(reflect_dot_eye, material.shininess);
			cont_specular = light.intensity * material.specular * factor;
		}
	}
	return cont_ambient + cont_diffuse + cont_specular;
}

Matrix KerrMath::position(const Ray& r, const double& t)
{
	return r.origin + r.direction * t;
}

Ray KerrMath::transform(const Ray& ray, const Matrix& m)
{
	Ray result((m * ray.origin), (m * ray.direction));
	return result;
}

std::vector<Intersection> KerrMath::intersectWorld(const World& world, const Ray& ray)
{
	std::vector<Intersection> xs, curr;
	for (int i = 0; i < world.shapes.size(); i++)
	{
		if (world.shapes[i]->type == "NONE") { throw KerrEngineException("EXCEPTION KERRMATH_INTERSECT_UNINITIALIZED_SHAPE"); }
		Ray ray2 = KerrMath::transform(ray, Matrix::inverse(world.shapes[i]->transform));
		if (world.shapes[i]->type == "SPHERE") { curr = KerrMath::localIntersectSphere(world.shapes[i], ray2); }
		else if (world.shapes[i]->type == "PLANE") { curr = KerrMath::localIntersectPlane(world.shapes[i], ray2); }
		else if (world.shapes[i]->type == "CUBE") { curr = KerrMath::localIntersectCube(world.shapes[i], ray2); }
		else { throw KerrEngineException("EXCEPTION KERRMATH_INTERSECT_UNKNOWN_SHAPE"); }
		if (curr.size() > 0)
		{	
			for (int j = 0; j < curr.size(); j++) { xs.push_back(curr[j]); }
		}
	}
	if (xs.size() == 0) { return xs; }
	std::sort(xs.begin(), xs.end());
	return xs;
}

std::vector<Intersection> KerrMath::localIntersectSphere(Shape* shape, const Ray& ray)
{
	std::vector<Intersection> ret;
	double a, b, c, discriminant;
	Matrix sphere_to_ray = ray.origin - Matrix::point(0.0, 0.0, 0.0);
	a = Matrix::dot(ray.direction, ray.direction);
	b = 2.0 * Matrix::dot(ray.direction, sphere_to_ray);
	c = Matrix::dot(sphere_to_ray, sphere_to_ray) - 1.0;
	discriminant = pow(b, 2.0) - 4.0 * a * c;
	if (discriminant < 0.0) { return ret; }
	double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	ret.push_back(Intersection(t1, shape));
	ret.push_back(Intersection(t2, shape));
	return ret;
}

std::vector<Intersection> KerrMath::localIntersectPlane(Shape* shape, const Ray& ray)
{
	std::vector<Intersection> ret;
	if (std::abs(ray.direction(1, 0)) < EPSILON) { return ret; }
	double t = -ray.origin(1, 0) / ray.direction(1, 0);
	ret.push_back(Intersection(t, shape));
	return ret;
}

std::vector<Intersection> KerrMath::localIntersectCube(Shape* shape, const Ray& ray)
{
	std::vector<Intersection> ret;
	std::vector<double> xt = KerrMath::checkAxis(ray.origin(0, 0), ray.direction(0, 0));
	std::vector<double> yt = KerrMath::checkAxis(ray.origin(1, 0), ray.direction(1, 0));
	std::vector<double> zt = KerrMath::checkAxis(ray.origin(2, 0), ray.direction(2, 0));
	double tmin = std::max(xt[0], std::max(yt[0], zt[0]));
	double tmax = std::min(xt[1], std::min(yt[1], zt[1]));
	if (tmin > tmax) { return ret; }
	ret.push_back(Intersection(tmin, shape));
	ret.push_back(Intersection(tmax, shape));
	return ret;
}

Matrix KerrMath::normalAt(Shape* shape, const Matrix& point)
{
	if (point.rows != 4 || point.cols != 1 || point(3, 0) != 1) { throw KerrEngineException("EXCEPTION_KERRMATH_NORMALATSPHEREINVALID_MATRIX_SIZE"); }
	if (shape->type == "NONE") { throw KerrEngineException("EXCEPTION KERRMATH_NORMALAT_UNINITIALIZED_SHAPE"); }
	Matrix local_point = Matrix::inverse(shape->transform) * point;
	Matrix local_normal;
	if (shape->type == "SPHERE") { local_normal = KerrMath::localNormalAtSphere(shape, local_point); }
	else if (shape->type == "PLANE") { local_normal = KerrMath::localNormalAtPlane(shape, local_point); }
	else if (shape->type == "CUBE") { local_normal = KerrMath::localNormalAtCube(shape, local_point); }
	else { throw KerrEngineException("EXCEPTION KERRMATH_NORMALAT_UNKNOWN_SHAPE"); }
	Matrix world_normal = Matrix::transpose(Matrix::inverse(shape->transform)) * local_normal;
	world_normal(3, 0) = 0.0;
	return Matrix::normalize(world_normal);
}

Matrix KerrMath::localNormalAtSphere(Shape* shape, const Matrix& point)
{
	if (point.rows != 4 || point.cols != 1 || point(3, 0) != 1) { throw KerrEngineException("EXCEPTION_KERRMATH_NORMALATSPHEREINVALID_MATRIX_SIZE"); }
	return point - Matrix::point(0.0, 0.0, 0.0);
}

Matrix KerrMath::localNormalAtPlane(Shape* shape, const Matrix& point)
{
	return Matrix::vector(0.0, 1.0, 0.0);
}

Matrix KerrMath::localNormalAtCube(Shape* shape, const Matrix& point)
{
	double maxc = std::max(std::abs(point(0, 0)), std::max(std::abs(point(1, 0)), std::abs(point(2, 0))));
	if (maxc == std::abs(point(0, 0))) { return Matrix::vector(point(0, 0), 0.0, 0.0); }
	else if (maxc == std::abs(point(1, 0))) { return Matrix::vector(0.0, point(1, 0), 0.0); }
	 return Matrix::vector(0.0, 0.0, point(2, 0));
}

Color KerrMath::shadeHit(const World& world, const Computations& comps, const int& remaining)
{
	Color surface = KerrMath::lighting(comps.obj->material, comps.obj, world.light, comps.over_point, comps.eyev, comps.normalv, KerrMath::isShadowed(world, comps.over_point));
	Color reflected = KerrMath::reflectedColor(world, comps, remaining);
	Color refracted = KerrMath::refractedColor(world, comps, remaining);
	if (comps.obj->material.reflective > 0.0 && comps.obj->material.transparency > 0.0)
	{
		double reflectance = KerrMath::schlick(comps);
		return surface + reflected * reflectance + refracted * (1.0 - reflectance);
	}
	return surface + reflected + refracted;
}

bool KerrMath::isShadowed(const World& world, const Matrix& point)
{
	Matrix v = world.light.position - point;
	double distance = Matrix::magnitude(v);
	Matrix direction = Matrix::normalize(v);
	Ray r(point, direction);
	std::vector<Intersection> xs = KerrMath::intersectWorld(world, r);
	Intersection h = Intersection::hit(xs);
	if (h.obj != nullptr && h.t < distance) { return true; }
	return false;
}

Color KerrMath::colorAt(const World& world, const Ray& ray, const int& remaining)
{
	std::vector<Intersection> xs = KerrMath::intersectWorld(world, ray);
	if (xs.size() == 0) { return Color(0.0, 0.0, 0.0); }
	Intersection i = Intersection::hit(xs);
	if (i.t <= 0.0) { return Color(0.0, 0.0, 0.0); }
	Computations comps = KerrMath::prepareComputations(i, ray, xs);
	return KerrMath::shadeHit(world, comps, remaining);
}

Color KerrMath::reflectedColor(const World& world, const Computations& comps, const int& remaining)
{
	if ((comps.obj->material.reflective == 0.0) || (remaining <= 0)) { return Color(0.0, 0.0, 0.0); }
	Ray reflect_ray(comps.over_point, comps.reflectv);
	Color color = KerrMath::colorAt(world, reflect_ray, remaining - 1);
	return color * comps.obj->material.reflective;
}

Color KerrMath::refractedColor(const World& world, const Computations& comps, const int& remaining)
{
	if (remaining == 0) { return Color(0.0, 0.0, 0.0); }
	if (comps.obj->material.transparency == 0.0) { return Color(0.0, 0.0, 0.0); }
	double n_ratio = comps.n1 / comps.n2;
	double cos_i = Matrix::dot(comps.eyev, comps.normalv);
	double sin2_t = std::pow(n_ratio, 2.0) * (1 - std::pow(cos_i, 2.0));
	if (sin2_t > 1.0) { return Color(0.0, 0.0, 0.0); }
	double cos_t = std::sqrt(1.0 - sin2_t);
	Matrix direction = comps.normalv * (n_ratio * cos_i - cos_t) - comps.eyev * n_ratio;
	Ray refract_ray(comps.under_point, direction);
	return KerrMath::colorAt(world, refract_ray, remaining - 1) * comps.obj->material.transparency;
}

Color KerrMath::patternAt(const Pattern& pattern, const Matrix& point)
{
	if (pattern.type == "stripe") { return ((int)std::floor(point(0, 0)) % 2 == 0) ? pattern.a : pattern.b; }
	else if (pattern.type == "ring") { return ((int)std::floor(std::sqrt(std::pow(point(0, 0), 2.0) + std::pow(point(2, 0), 2.0))) % 2 == 0) ? pattern.a : pattern.b; }
	else if (pattern.type == "gradient") { return pattern.a + (pattern.b - pattern.a) * (point(0, 0) - std::floor(point(0, 0))); }
	else if (pattern.type == "checkers") { return ((int)(std::floor(point(0, 0)) + std::floor(point(1, 0)) + std::floor(point(2, 0))) % 2 == 0) ? pattern.a : pattern.b; }
	else if (pattern.type == "test") { return Color(point(0, 0), point(1, 0), point(2, 0)); }
	throw KerrEngineException("EXCEPTION_KERRMATH_STRIPEAT_UNSUPPORTED_PATTERN_TYPE");
}

Color KerrMath::patternAtShape(const Pattern& pattern, Shape* object, const Matrix& world_point)
{
	Matrix object_point = Matrix::inverse(object->transform) * world_point;
	Matrix pattern_point = Matrix::inverse(pattern.transform) * object_point;
	return KerrMath::patternAt(pattern, pattern_point);
}

double KerrMath::schlick(const Computations& comps)
{
	double cos = Matrix::dot(comps.eyev, comps.normalv);
	if (comps.n1 > comps.n2)
	{
		double n = comps.n1 / comps.n2;
		double sin2_t = std::pow(n, 2.0) * (1.0 - std::pow(cos, 2.0));
		if (sin2_t > 1.0) { return 1.0; }
		double cos_t = std::sqrt(1.0 - sin2_t);
		cos = cos_t;
	}
	double r0 = std::pow(((comps.n1 - comps.n2) / (comps.n1 + comps.n2)), 2.0);
	return r0 + (1 - r0) * std::pow((1 - cos), 5.0);
}

std::vector<double> KerrMath::checkAxis(const double& origin, const double& direction)
{
	std::vector<double> ret;
	double tmin = 0.0;
	double tmax = 0.0;
	double tmin_numerator = -1.0 - origin;
	double tmax_numerator = 1.0 - origin;
	if (std::abs(direction) >= EPSILON)
	{
		tmin = tmin_numerator / direction;
		tmax = tmax_numerator / direction;
	}
	else
	{
		tmin = tmin_numerator * std::numeric_limits<double>::infinity();
		tmax = tmax_numerator * std::numeric_limits<double>::infinity();
	}
	ret.push_back(tmin);
	ret.push_back(tmax);
	if (tmin > tmax) { std::reverse(ret.begin(), ret.end()); }
	return ret;
}