// Matthew Kerr

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "tuple.h"
#include "matrix.h"

class Tuple;
class Matrix;

Matrix translation(const double& x, const double& y, const double& z);
Matrix scaling(const double& x, const double& y, const double& z);
Matrix rotation_x(const double& r);
Matrix rotation_y(const double& r);
Matrix rotation_z(const double& r);
Matrix shearing(const double& x_y, const double& x_z, const double& y_x, const double& y_z, const double& z_x, const double& z_y);
Matrix view_transform(const Tuple& from, const Tuple& to, const Tuple& up);

#endif