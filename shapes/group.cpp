// Matthew Kerr

#include "group.h"

Group::Group() : Shape() { }

void Group::add_child(Shape *s) {
	_shapes.push_back(s);
	s->_parent = (Shape *)this;
	_bounds.add_box(s->parent_space_bounds());
}

std::vector<std::vector<Shape *>> Group::partition_children() {
	std::vector<BoundingBox> split = _bounds.split_bounds();
	std::vector<Shape *> left;
	std::vector<Shape *> right;
	std::vector<std::vector<Shape *>> partitioned;
	for (int i = 0; i < _shapes.size(); i++) {
		BoundingBox transformed_bounds(_shapes[i]->_transform * _shapes[i]->bounds()._min, _shapes[i]->_transform * _shapes[i]->bounds()._max);
		if (split[0].contains_box(transformed_bounds)) {
			left.push_back(_shapes[i]);
			_shapes.erase(_shapes.begin() + i--);
		} else if (split[1].contains_box(transformed_bounds)) {
			right.push_back(_shapes[i]);
			_shapes.erase(_shapes.begin() + i--);
		}
	}
	partitioned.push_back(left);
	partitioned.push_back(right);
	return partitioned;
}

void Group::make_subgroup(std::vector<Shape *> shapes) {
	if (shapes.size() == 0) { return; }
	Group *g = new Group();
	for (int i = 0; i < shapes.size(); i++) { g->add_child(shapes[i]); }
	_shapes.push_back(g);
}

const Intersections Group::local_intersect(Ray ray) const {
	Intersections xs;
	if (_bounds.intersects(ray)) {
		//Ray ray2 = transform_ray(ray, inverse(_transform));
		for (int i = 0; i < _shapes.size(); i++) {
			xs.merge(_shapes[i]->intersect(ray));
		}
	}
	return xs;
}

const Tuple Group::local_normal_at(Tuple local_point) const {
	throw std::invalid_argument("Group::local_normal_at should never be called.");
	return local_point;
}

const BoundingBox Group::bounds() const {
	return _bounds;
}

void Group::divide(const int &threshold) {
	if (threshold <= _shapes.size()) {
		std::vector<std::vector<Shape *>> partitioned = partition_children();
		if (partitioned[0].size() > 0) { make_subgroup(partitioned[0]); }
		if (partitioned[1].size() > 0) { make_subgroup(partitioned[1]); }
	}
	for (int i = 0; i < _shapes.size(); i++) { _shapes[i]->divide(threshold); }
}

void Group::delete_children() {
	for (int i = 0; i < _shapes.size(); i++) {
		_shapes[i]->delete_children();
		delete _shapes[i];
		_shapes.erase(_shapes.begin() + i--);
	}
}