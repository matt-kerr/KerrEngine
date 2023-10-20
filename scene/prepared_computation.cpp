// Matthew Kerr

#include "prepared_computation.h"

std::ostream& operator<<(std::ostream &out, const PreparedComputation &comps) {
    std::cout << "PreparedComputation:" << std::endl
		<< "  t: " << comps._t << std::endl
		<< "  obj: " << (*comps._obj) << std::endl
		<< "  point: " << comps._point << std::endl
		<< "  over_point: " << comps._over_point << std::endl
		<< " under_point: " << comps._under_point << std::endl
		<< "  eyev: " << comps._eyev << std::endl
		<< "  normalv: " << comps._normalv << std::endl
		<< "  reflectv: " << comps._reflectv << std::endl
		<< "  inside: " << comps._inside << std::endl
		<< " n1: " << comps._n1 << std::endl
		<< " n2: " << comps._n2 << std::endl;
    return out;
}

PreparedComputation::PreparedComputation(Intersection hit, Ray ray, Intersections xs)
{
	_t = hit._t;
	_obj = (Shape *)hit._obj;
	_point = position(ray, _t);
	_eyev = -ray._direction;
	_normalv = _obj->normal_at(_point);
	if (dot(_normalv, _eyev) < 0.0) {
		_inside = true;
		_normalv = -_normalv;
	} else {
		_inside = false;
	}
	_over_point = _point + _normalv * EPSILON;
	_under_point = _point - _normalv * EPSILON;
	_reflectv = reflect(ray._direction, _normalv);

	std::vector<Shape *> containers;
	_n1 = -1.0;
	_n2 = -1.0;
	for (int i = 0; i < xs.count(); i++) {
		if (xs[i] == hit) {
			if (containers.size() == 0) {
				_n1 = 1.0;
			} else {
				_n1 = containers.back()->_material._refractive_index;
			}
		}
		if (std::find(containers.begin(), containers.end(), (Shape *)xs[i]._obj) != containers.end()) {
			containers.erase(std::remove(containers.begin(), containers.end(), xs[i]._obj), containers.end());
		} else {
			containers.push_back((Shape *)xs[i]._obj);
		}
		if (xs[i] == hit)
		{
			if (containers.size() == 0) {
				_n2 = 1.0;
			} else {
				_n2 = containers.back()->_material._refractive_index;
			}
			break;
		}
	}
}

