#include "KerrMath.h"

Computations KerrMath::prepareComputations(Intersection intersection, Ray ray)
{
	if (intersection.obj->type == "NONE") { throw KerrEngineException("EXCEPTION KERRMATH_PREPARECOMPUTATIONS_UNINITIALIZED_SHAPE"); }
	if (intersection.obj->type == "SPHERE")
	{
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
	throw KerrEngineException("EXCEPTION KERRMATH_PREPARECOMPUTATIONS_UNKNOWN_SHAPE");
}

Color KerrMath::lighting(const Material& material, const PointLight& light, const Matrix& point, const Matrix& eyev, const Matrix& normalv, const bool& in_shadow)
{
	Color black(0.0, 0.0, 0.0);
	Color effective_color = material.color * light.intensity;
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

Ray KerrMath::transform(const Ray& r, const Matrix& m)
{
	Ray result((m * r.origin), (m * r.direction));
	return result;
}

std::vector<Intersection> KerrMath::intersectWorld(const World& world, const Ray& ray)
{
	std::vector<Intersection> xs, curr;
	for (int i = 0; i < world.shapes.size(); i++)
	{
		if (world.shapes[i]->type == "NONE") { throw KerrEngineException("EXCEPTION KERRMATH_INTERSECT_UNINITIALIZED_SHAPE"); }
		if (world.shapes[i]->type == "SPHERE") { curr = KerrMath::localIntersectSphere(world.shapes[i], ray); }
		else if (world.shapes[i]->type == "PLANE") { curr = KerrMath::localIntersectPlane(world.shapes[i], ray); }
		else { throw KerrEngineException("EXCEPTION KERRMATH_INTERSECT_UNKNOWN_SHAPE"); }
		if (curr.size() > 0)
		{
			xs.push_back(curr[0]);
			xs.push_back(curr[1]);
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
	std::vector<Intersection> ret;
	if (ray.direction(1, 0) < EPSILON) { return ret; }
	double t = -ray.origin(1, 0) / ray.direction(1, 0);
	ret.push_back(Intersection(t, shape));
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
	else { throw KerrEngineException("EXCEPTION KERRMATH_NORMALAT_UNKNOWN_SHAPE"); }
	Matrix world_normal = Matrix::transpose(Matrix::inverse(shape->transform)) * local_normal;
	world_normal(3, 0) = 0.0;
	return Matrix::normalize(world_normal);
}

Matrix KerrMath::localNormalAtSphere(Shape* shape, const Matrix& local_point)
{
	if (local_point.rows != 4 || local_point.cols != 1 || local_point(3, 0) != 1) { throw KerrEngineException("EXCEPTION_KERRMATH_NORMALATSPHEREINVALID_MATRIX_SIZE"); }
	return local_point - Matrix::point(0.0, 0.0, 0.0);
}

Matrix KerrMath::localNormalAtPlane(Shape* sphere, const Matrix& world_point)
{
	return Matrix::vector(0.0, 1.0, 0.0);
}


Color KerrMath::shadeHit(const World& world, const Computations& comps)
{
	return KerrMath::lighting(comps.obj->material, world.light, comps.over_point, comps.eyev, comps.normalv, KerrMath::isShadowed(world, comps.over_point));
}

Color KerrMath::colorAt(const World& world, const Ray& ray)
{
	std::vector<Intersection> xs = KerrMath::intersectWorld(world, ray);
	if (xs.size() == 0) { return Color(0.0, 0.0, 0.0); }
	Intersection i = Intersection::hit(xs);
	if (i.t < 0.0) { return Color(0.0, 0.0, 0.0); }
	Computations comps = KerrMath::prepareComputations(i, ray);
	return KerrMath::shadeHit(world, comps);
}

bool KerrMath::isShadowed(const World& world, const Matrix& point)
{
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

