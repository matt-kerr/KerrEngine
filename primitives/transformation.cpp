#include "transformation.h"

Matrix translation(const double& x, const double& y, const double& z) {
    return Matrix(4, 4, std::vector<double> { 1.0, 0.0, 0.0, x,
                                            0.0, 1.0, 0.0, y,
                                            0.0, 0.0, 1.0, z,
                                            0.0, 0.0, 0.0, 1.0 });
}

Matrix scaling(const double& x, const double& y, const double& z) {
    return Matrix(4, 4, std::vector<double> { x, 0.0, 0.0, 0.0,
                                            0.0, y, 0.0, 0.0,
                                            0.0, 0.0, z, 0.0,
                                            0.0, 0.0, 0.0, 1.0 });
}

Matrix rotation_x(const double& r) {
    return Matrix(4, 4, std::vector<double> { 1.0, 0.0, 0.0, 0.0,
                                            0.0, std::cos(r), -std::sin(r), 0.0,
                                            0.0, std::sin(r), std::cos(r), 0.0,
                                            0.0, 0.0, 0.0, 1.0 });
}

Matrix rotation_y(const double& r) {
    return Matrix(4, 4, std::vector<double> { std::cos(r), 0.0, std::sin(r), 0.0,
                                            0.0, 1.0, 0.0, 0.0,
                                            -std::sin(r), 0.0, std::cos(r), 0.0,
                                            0.0, 0.0, 0.0, 1.0 });
}

Matrix rotation_z(const double& r) {
    return Matrix(4, 4, std::vector<double> { std::cos(r), -std::sin(r), 0.0, 0.0,
                                            std::sin(r), std::cos(r), 0.0, 0.0,
                                            0.0, 0.0, 1.0, 0.0,
                                            0.0, 0.0, 0.0, 1.0 });
}

Matrix shearing(const double& x_y, const double& x_z, const double& y_x, const double& y_z, const double& z_x, const double& z_y) {
    return Matrix(4, 4, std::vector<double> { 1.0, x_y, x_z, 0.0,
                                            y_x, 1.0, y_z, 0.0,
                                            z_x, z_y, 1.0, 0.0,
                                            0.0, 0.0, 0.0, 1.0 });
}

Matrix view_transform(const Tuple& from, const Tuple& to, const Tuple& up) {
	Tuple forward = normalize(to - from);
	Tuple upn = normalize(up);
	Tuple left = cross(forward, upn);
	Tuple true_up = cross(left, forward);
	Matrix orientation(4, 4, std::vector<double> { left._x, left._y, left._z, 0.0,
                                                  true_up._x, true_up._y, true_up._z, 0.0,
                                                  -forward._x, -forward._y, -forward._z, 0.0,
                                                  0.0, 0.0, 0.0, 1.0 });
	return orientation * translation(-from._x, -from._y, -from._z);
}