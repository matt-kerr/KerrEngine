// Matthew Kerr

#include "intersections.h"

Intersections::Intersections() { }

Intersections::Intersections(std::vector<Intersection> intersections) {
    _intersections = intersections;
}

Intersection Intersections::operator[](const int &index) {
    return _intersections[index];
}

void Intersections::merge(Intersection other) {
	std::vector<Intersection> temp;
	temp.push_back(other);
	merge(temp);
}

void Intersections::merge(Intersections other) {
	std::vector<Intersection> merged;
	std::vector<Intersection>::const_iterator iter_curr = _intersections.begin();
	std::vector<Intersection>::const_iterator iter_other = other._intersections.begin();
	while (iter_curr != _intersections.end() && iter_other != other._intersections.end()) {
		if ((*iter_curr)._t < (*iter_other)._t) {
			merged.push_back(*iter_curr);
			iter_curr++;
		} else {
			merged.push_back(*iter_other);
			iter_other++;
		}
	}
	while (iter_curr != _intersections.end()) {
		merged.push_back(*iter_curr);
		iter_curr++;
	}
	while (iter_other != other._intersections.end()) {
		merged.push_back(*iter_other);
		iter_other++;
	}
	_intersections = merged;
}

Intersection hit(Intersections xs) {
	for (int i = 0; i < xs.count(); i++) {
		if (xs[i]._t > 0.0) {
			return xs[i];
		}
	}
	return Intersection(0.0, nullptr);
}