// Matthew Kerr

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <numbers>
#include <string>
using namespace std;

class Matrix
{
	friend std::ostream& operator<<(std::ostream& out, const Matrix& m);

	public:
		int rows;
		int cols;
		std::string type;
		double * data;

		// constructors
		Matrix();
		virtual ~Matrix();
		Matrix(int rows, int cols);
		Matrix(const Matrix& orig); // copy constructor
		Matrix(Matrix&& orig) noexcept; // move constructor

		// operator overloads
		Matrix& operator=(const Matrix& rhs); // = operator overload
		Matrix& operator=(Matrix&& orig); // move = operator overload (move assignment overload)
		bool operator==(const Matrix& rhs); // == operator overload
		Matrix operator-() const; // - negation operator overload
		Matrix& operator[](const int& index); // [] writing overload (not allowed)
		const Matrix& operator[](const int& index) const; // [] reading overload (not allowed)
		double& operator()(const int& row, const int& col); // m(x, y) writing overload
		double operator()(const int& row, const int& col) const; // m(x, y) reading overload
		Matrix operator+(const Matrix& rhs) const; // Matrix + Matrix operator overload
		Matrix operator-(const Matrix& rhs) const; // Matrix - Matrix operator overload
		Matrix operator*(const Matrix& rhs) const; // Matrix * Matrix operator overload
		Matrix operator*(const double& rhs) const; // Matrix * scalar operator overload
		Matrix operator/(const double& rhs) const; // Matrix / scalar operator overload

		// matrix functions
		static void printPiValues();
		static Matrix submatrix(const Matrix& m, const int& row_elim, const int& col_elim);
		static Matrix normalize(const Matrix& m); // vector mode only
		static Matrix identity(const int& size);
		static Matrix transpose(const Matrix& m);
		static bool isInvertible(const Matrix& m);
		static Matrix inverse(const Matrix& m);
		static Matrix vector(const double& x, const double& y, const double& z);
		static Matrix point(const double& x, const double& y, const double& z);
		static Matrix translation(const double& x, const double& y, const double& z);
		static Matrix scaling(const double& x, const double& y, const double& z);
		static Matrix rotationX(const double& r);
		static Matrix rotationY(const double& r);
		static Matrix rotationZ(const double& r);
		static Matrix shearing(const double& x_y, const double& x_z, const double& y_x, const double& y_z, const double& z_x, const double& z_y);
		static Matrix cross(const Matrix& lhs, const Matrix& rhs);
		static double dot(const Matrix& lhs, const Matrix& rhs); // vector
		static double dot(const Matrix& lhs, const Matrix& rhs, const int& row, const int& col); // matrix
		static double determinant(const Matrix& m);
		static double minor(const Matrix& m, const int& elim_row, const int& elim_col);
		static double cofactor(const Matrix& m, const int& elim_row, const int& elim_col);
		static double magnitude(const Matrix& m);
		static Matrix reflect(const Matrix& in, const Matrix& normal); // vector mode only
		static Matrix viewTransform(const Matrix& from, const Matrix& to, const Matrix& up);
};

#endif