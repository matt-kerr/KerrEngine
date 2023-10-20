// Matthew Kerr

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <iomanip>
#include "../kerr_inline.h"
#include "tuple.h"

class Tuple;
class Matrix
{
    friend std::ostream& operator<<(std::ostream &out, const Matrix &m);

    public:
        int _r;
        int _c;
        double *_data;

        Matrix();
        Matrix(const int &r, const int &c);
        Matrix(const int &r, const int &c, const std::vector<double> &values);
        Matrix(const Matrix &orig);
        virtual ~Matrix() { free(_data); }

        double& operator()(const int &x, const int &y); // m(x, y) writing overload
        double operator()(const int &x, const int &y) const; // m(x, y) reading overload
        Matrix &operator=(const Matrix &orig);

    private:
        inline int matrix_to_index(const int &row, const int &col) const { return col + row * _c; }
};

bool operator==(const Matrix &lhs, const Matrix &rhs);
bool operator!=(const Matrix &lhs, const Matrix &rhs);
Matrix operator*(const Matrix &lhs, const Matrix &rhs);
Tuple operator*(const Matrix &lhs, const Tuple &rhs);

Matrix identity_matrix(const int &size);
double dot(const Matrix &lhs, const Matrix &rhs, const int &row, const int &col);
Matrix transpose(const Matrix &m);
double determinant(const Matrix& m);
double cofactor(const Matrix& m, const int& elim_row, const int& elim_col);
Matrix submatrix(const Matrix& m, const int& row_elim, const int& col_elim);
double minor(const Matrix& m, const int& elim_row, const int& elim_col);
bool is_invertible(const Matrix& m);
Matrix inverse(const Matrix& m);
//Matrix viewtransform(const Matrix &from, const Matrix &to, const Matrix &up);
//void PrintPiValues();
//Matrix reflect(const Matrix &in, const Matrix &normal); // vector mode only

#endif