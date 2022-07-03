#include "KerrMath.h"

Computations KerrMath::prepareComputations(Intersection intersection, Ray ray)
{
	if (DEBUG)
	{
		cout << "entered KerrMath::prepareComputations" << endl;
		cout << "intersection.obj->type = " << intersection.obj->type << endl;
	}
	if (intersection.obj->type == "NONE") { throw KerrEngineException("EXCEPTION KERRMATH_PREPARECOMPUTATIONS_UNINITIALIZED_SHAPE"); }
	Matrix point = KerrMath::position(ray, intersection.t);
	Matrix eyev = -ray.direction;
	Matrix normalv = KerrMath::normalAt(intersection.obj, point);
	bool inside = false;
	if (Matrix::dot(normalv, eyev) < 0.0)
	{
		inside = true;
		normalv = -normalv;
	}
	else
	{
		inside = false;
	}
	Matrix over_point = point + normalv * EPSILON;
	return Computations(intersection.t, intersection.obj, point, over_point, eyev, normalv, inside);
}

Color KerrMath::lighting(const Material& material, Shape* object, const PointLight& light, const Matrix& point, const Matrix& eyev, const Matrix& normalv, const bool& in_shadow)
{
	if (DEBUG) { cout << "entered KerrMath::lighting" << endl; }
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
	if (DEBUG) { cout << "entered KerrMath::position" << endl; }
	return r.origin + r.direction * t;
}

Ray KerrMath::transform(const Ray& ray, const Matrix& m)
{
	if (DEBUG)
	{
		cout << "entered KerrMath::transform" << endl;
		cout << "ray.origin = " << ray.origin;
		cout << "ray.direction = " << ray.direction << endl;
	}
	Ray result((m * ray.origin), (m * ray.direction));
	return result;
}

std::vector<Intersection> KerrMath::intersectWorld(const World& world, const Ray& ray)
{
	if (DEBUG)
	{
		cout << "entered KerrMath::intersectWorld" << endl;
		cout << "world.shapes[0].type = " << world.shapes[0]->type << endl;
		cout << "world.shapes[0].transform = " << endl << world.shapes[0]->transform << endl;
	}
	std::vector<Intersection> xs, curr;
	for (int i = 0; i < world.shapes.size(); i++)
	{
		if (world.shapes[i]->type == "NONE") { throw KerrEngineException("EXCEPTION KERRMATH_INTERSECT_UNINITIALIZED_SHAPE"); }
		if (world.shapes[i]->type == "SPHERE") { curr = KerrMath::localIntersectSphere(world.shapes[i], ray); }
		else if (world.shapes[i]->type == "PLANE") { curr = KerrMath::localIntersectPlane(world.shapes[i], ray); }
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
	if (DEBUG)
	{
		cout << "entered KerrMath::localIntersectSphere" << endl;
		cout << "shape->type = " << shape->type << endl;
		cout << "shape->transform = " << endl << shape->transform << endl;
	}
	std::vector<Intersection> ret;
	double a, b, c, discriminant;
	Ray ray2 = KerrMath::transform(ray, Matrix::inverse(shape->transform));
	Matrix sphere_to_ray = ray2.origin - Matrix::point(0.0, 0.0, 0.0);
	a = Matrix::dot(ray2.direction, ray2.direction);
	b = 2.0 * Matrix::dot(ray2.direction, sphere_to_ray);
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
	if (DEBUG)
	{
		cout << "entered KerrMath::localIntersectPlane" << endl;
		cout << "shape->type = " << shape->type << endl;
		cout << "shape->transform = " << endl << shape->transform << endl;
	}
	std::vector<Intersection> ret;
	Ray ray2 = KerrMath::transform(ray, Matrix::inverse(shape->transform));
	if (std::abs(ray2.direction(1, 0)) < EPSILON) { return ret; }
	double t = -ray2.origin(1, 0) / ray2.direction(1, 0);
	ret.push_back(Intersection(t, shape));
	return ret;
}

Matrix KerrMath::normalAt(Shape* shape, const Matrix& point)
{
	if (DEBUG) { cout << "entered KerrMath::normalAt" << endl; }
	if (point.rows != 4 || point.cols != 1 || point(3, 0) != 1) { throw KerrEngineException("EXCEPTION_KERRMATH_NORMALATSPHEREINVALID_MATRIX_SIZE"); }
	if (shape->type == "NONE") { throw KerrEngineException("EXCEPTION KERRMATH_NORMALAT_UNINITIALIZED_SHAPE"); }
	Matrix local_point = Matrix::inverse(shape->transform) * point;
	Matrix local_normal;
	if (shape->type == "SPHERE") { local_normal = KerrMath::localNormalAtSphere(shape, local_point); }
	else if (shape->type == "PLANE") { local_normal = KerrMath::localNormalAtPlane(shape, local_point); }
	else { throw KerrEngineException("EXCEPTION KERRMATH_NORMALAT_UNKNOWN_SHAPE"); }
	Matrix world_normal = Matrix::transpose(Matrix::inverse(shape->transform)) * local_normal;
	world_normal(3, 0) = 0.0;
	return Matrix::normalize(world_normal);
}

Matrix KerrMath::localNormalAtSphere(Shape* shape, const Matrix& local_point)
{
	if (DEBUG) { cout << "entered KerrMath::localNormalAtSphere" << endl; }
	if (local_point.rows != 4 || local_point.cols != 1 || local_point(3, 0) != 1) { throw KerrEngineException("EXCEPTION_KERRMATH_NORMALATSPHEREINVALID_MATRIX_SIZE"); }
	return local_point - Matrix::point(0.0, 0.0, 0.0);
}

Matrix KerrMath::localNormalAtPlane(Shape* shape, const Matrix& world_point)
{
	if (DEBUG) { cout << "entered KerrMath::localNormalAtPlane" << endl; }
	return Matrix::vector(0.0, 1.0, 0.0);
}


Color KerrMath::shadeHit(const World& world, const Computations& comps)
{
	if (DEBUG) { cout << "entered KerrMath::shadeHit" << endl; }
	return KerrMath::lighting(comps.obj->material, comps.obj, world.light, comps.over_point, comps.eyev, comps.normalv, KerrMath::isShadowed(world, comps.over_point));
}

bool KerrMath::isShadowed(const World& world, const Matrix& point)
{
	if (DEBUG) { cout << "entered KerrMath::isShadowed" << endl; }
	Matrix v = world.light.position - point;
	double distance = Matrix::magnitude(v);
	Matrix direction = Matrix::normalize(v);
	Ray r(point, direction);
	std::vector<Intersection> xs = KerrMath::intersectWorld(world, r);
	Intersection h = Intersection::hit(xs);
	if (h.t == -999.0) { return false; }
	if (h.t > 0.0 && h.t < distance) { return true; }
	return false;
}

Color KerrMath::colorAt(const World& world, const Ray& ray)
{
	if (DEBUG)
	{
		cout << "entered KerrMath::colorAt" << endl;
		cout << "world.shapes[0].type = " << world.shapes[0]->type << endl;
		cout << "world.shapes[0].transform = " << endl << world.shapes[0]->transform << endl;
	}
	std::vector<Intersection> xs = KerrMath::intersectWorld(world, ray);
	if (DEBUG) { cout << "KerrMath::colorAt xs.size() = " << xs.size(); }
	if (xs.size() == 0) { return Color(0.0, 0.0, 0.0); }
	Intersection i = Intersection::hit(xs);
	if (DEBUG) { cout << "KerrMath::colorAt i.t = " << i.t; }
	if (i.t <= 0.0) { return Color(0.0, 0.0, 0.0); }
	Computations comps = KerrMath::prepareComputations(i, ray);
	return KerrMath::shadeHit(world, comps);
}

Color KerrMath::patternAt(const Pattern& pattern, const Matrix& point)
{
	if (pattern.type == "stripe") { return ((int)std::floor(point(0, 0)) % 2 == 0) ? pattern.a : pattern.b; }
	else if (pattern.type == "test") { return Color(point(0, 0), point(1, 0), point(2, 0)); }
	else if (pattern.type == "ring") { return ((int)std::floor(std::sqrt(std::pow(point(0, 0), 2.0) + std::pow(point(2, 0), 2.0))) % 2 == 0) ? pattern.a : pattern.b; }
	else if (pattern.type == "gradient") { return pattern.a + (pattern.b - pattern.a) * (point(0, 0) - std::floor(point(0, 0))); }
	else if (pattern.type == "checkers") { return ((int)(std::abs(point(0, 0)) + std::abs(point(1, 0)) + std::abs(point(2, 0))) % 2 == 0) ? pattern.a : pattern.b; }
	throw KerrEngineException("EXCEPTION_PATTERN_STRIPEAT_UNSUPPORTED_PATTERN_TYPE");
}

Color KerrMath::patternAtShape(const Pattern& pattern, Shape* object, const Matrix& world_point)
{
	Matrix object_point = Matrix::inverse(object->transform) * world_point;
	Matrix pattern_point = Matrix::inverse(pattern.transform) * object_point;
	return KerrMath::patternAt(pattern, pattern_point);
}