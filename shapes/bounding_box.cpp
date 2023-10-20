#include "bounding_box.h"

std::ostream& operator<<(std::ostream &out, const BoundingBox &b) {
	std::cout << "BoundingBox(min = " << b._min << ", max = " << b._max << ")" << std::endl;
	return out;
}

BoundingBox::BoundingBox() {
    _min = create_point(BIG_NUM, BIG_NUM, BIG_NUM);
    _max = create_point(-BIG_NUM, -BIG_NUM, -BIG_NUM);
}

BoundingBox::BoundingBox(Tuple min, Tuple max) {
    _min = min;
    _max = max;
}

void BoundingBox::add_point(Tuple point) {
    _min._x = (point._x < _min._x) ? point._x : _min._x;
    _min._y = (point._y < _min._y) ? point._y : _min._y;
    _min._z = (point._z < _min._z) ? point._z : _min._z;
    _max._x = (point._x > _max._x) ? point._x : _max._x;
    _max._y = (point._y > _max._y) ? point._y : _max._y;
    _max._z = (point._z > _max._z) ? point._z : _max._z;
}

void BoundingBox::add_box(BoundingBox box) {
    add_point(box._min);
    add_point(box._max);
}

bool BoundingBox::contains_point(Tuple point) {
    return _min._x <= point._x && point._x <= _max._x
        && _min._y <= point._y && point._y <= _max._y
        && _min._z <= point._z && point._z <= _max._z;
}

bool BoundingBox::contains_box(BoundingBox box) {
    return contains_point(box._min) && contains_point(box._max);
}

bool BoundingBox::intersects(Ray ray) const {
	std::vector<double> xt = check_axis(ray._origin._x, ray._direction._x, _min._x, _max._x);
	std::vector<double> yt = check_axis(ray._origin._y, ray._direction._y, _min._y, _max._y);
	std::vector<double> zt = check_axis(ray._origin._z, ray._direction._z, _min._z, _max._z);
	double tmin = std::max(xt[0], std::max(yt[0], zt[0]));
	double tmax = std::min(xt[1], std::min(yt[1], zt[1]));
	return tmin <= tmax;
}

BoundingBox BoundingBox::transform(Matrix transform) {
    BoundingBox ret;
    ret.add_point(transform * _min);
    ret.add_point(transform * create_point(_min._x, _min._y, _max._z));
    ret.add_point(transform * create_point(_min._x, _max._y, _min._z));
    ret.add_point(transform * create_point(_min._x, _max._y, _max._z));
    ret.add_point(transform * create_point(_max._x, _min._y, _min._z));
    ret.add_point(transform * create_point(_max._x, _min._y, _max._z));
    ret.add_point(transform * create_point(_max._x, _max._y, _min._z));
    ret.add_point(transform * _max);
    return ret;
}

std::vector<BoundingBox> BoundingBox::split_bounds() {
    double dx = std::abs(_max._x - _min._x);
    double dy = std::abs(_max._y - _min._y);
    double dz = std::abs(_max._z - _min._z);
    double greatest = std::max(dx, std::max(dy, dz));
    double x0 = _min._x;
    double y0 = _min._y;
    double z0 = _min._z;
    double x1 = _max._x;
    double y1 = _max._y;
    double z1 = _max._z;

    if (greatest == dx) { x0 = x1 = x0 + dx / 2.0; }
    else if (greatest == dy) { y0 = y1 = y0 + dy / 2.0; }
    else { z0 = z1 = z0 + dz / 2.0; }

    Tuple mid_min = create_point(x0, y0, z0);
    Tuple mid_max = create_point(x1, y1, z1);

    BoundingBox left(_min, mid_max);
    BoundingBox right(mid_min, _max);
    std::vector<BoundingBox> boxes;
    boxes.push_back(left);
    boxes.push_back(right);

    return boxes;
}