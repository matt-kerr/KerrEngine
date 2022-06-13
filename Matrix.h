// Matthew Kerr

#ifndef MATRIX_H
#define MATRIX_H
#define EPSILON 0.0001
#define VECTOR 0
#define POINT 1

#include <iostream>
#include <numbers>
using namespace std;

class Matrix
{
	friend std::ostream& operator<<(std::ostream& out, const Matrix& m);

	public:
		int rows;
		int cols;
		double * data;

		// constructors
		Matrix();
		virtual ~Matrix();
		Matrix(int rows, int cols);
		Matrix(Matrix& orig); // copy constructor
		Matrix(Matrix&& orig) noexcept; // move constructor

		// operator overloads
		Matrix& operator=(const Matrix& rhs); // = operator overload
		Matrix& operator=(Matrix&& orig); // move = operator overload (move assignment overload)
		bool operator==(const Matrix& orig); // == operator overload
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
		void printPiValues();
		static Matrix createVector(const double& x, const double& y, const double& z);
		void vector(const double& x, const double& y, const double& z);
		static Matrix createPoint(const double& x, const double& y, const double& z);
		void point(const double& x, const double& y, const double& z);
		void resize(const int& rows, const int& cols);
		void identity(const int& size);
		Matrix transpose();
		const double dotProductMatrix(const Matrix& rhs, const int& row, const int& col) const;
		const double dotProductVector(const Matrix& rhs) const;
		Matrix crossProductVector(const Matrix& rhs);
		double determinant();
		double minor(const int& elim_row, const int& elim_col);
		double cofactor(const int& elim_row, const int& elim_col);
		Matrix getSubmatrix(const int& row_elim, const int& col_elim);
		bool isInvertible();
		Matrix inverse();
		void translation(const double& x, const double& y, const double& z);
		void scaling(const double& x, const double& y, const double& z);
		void rotation_x(const double& r);
		void rotation_y(const double& r);
		void rotation_z(const double& r);
		void shearing(const double& x_y, const double& x_z, const double& y_x, const double& y_z, const double& z_x, const double& z_y);
		Matrix normalize(); // vector mode only
		double magnitude();
		Matrix reflect(const Matrix& normal); // vector mode only
};

#endif