// Matthew Kerr

#include "matrix.h"

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
    for (int i = 0; i < m._r; i++) {
        for (int j = 0; j < m._c; j++) {
            std::cout << std::setw(5) << m(i, j);
            if (j < m._c - 1) { std::cout << " "; }
        }
        std::cout << std::endl;
    }
    return out;
}

Matrix::Matrix() {
	_r = 4;
	_c = 4;
	_data = (double *)calloc(_r * _c, sizeof(double));
	for (int i = 0; i < _r; i++) {
		(*this)(i, i) = 1.0;
	}
}

Matrix::Matrix(const int &r, const int &c) {
	_r = r;
	_c = c;
	_data = (double *)calloc(r * c, sizeof(double));
}

Matrix::Matrix(const int &r, const int &c, const std::vector<double> &values) {
	_r = r;
	_c = c;
	_data = (double *)calloc(_r * _c, sizeof(double));
	for (int i = 0; i < values.size(); i++) {
		_data[i] = values[i];
	}
}

Matrix::Matrix(const Matrix &orig) {
	_r = orig._r;
	_c = orig._c;
	_data = (double *)calloc(_r * _c, sizeof(double));
	memcpy(_data, orig._data, _r * _c * sizeof(double));
}

double& Matrix::operator()(const int &x, const int &y)
{
	if (x >= _r || y >= _c) { throw std::invalid_argument("Invalid arguments in matrix operator() writing overload"); }
	return _data[matrix_to_index(x, y)];
}

double Matrix::operator()(const int& x, const int& y) const
{
	if (x >= _r || y >= _c) { throw std::invalid_argument("Invalid arguments in matrix operator() reading overload"); }
	return _data[matrix_to_index(x, y)];
}

Matrix &Matrix::operator=(const Matrix &orig) {
	if (this != &orig) {
		if (_r != orig._r || _c != orig._c) {
			free(_data);
			_r = orig._r;
			_c = orig._c;
			_data = (double *)calloc(_r * _c, sizeof(double));
		}
		memcpy(_data, orig._data, _r * _c * sizeof(double));
	}
	return *this;
}

bool operator==(const Matrix &lhs, const Matrix &rhs) {
	if (lhs._r != rhs._r || lhs._c != rhs._c) { return false; }
	for (int i = 0; i < lhs._r; i++) {
		for (int j = 0; j < lhs._c; j++) {
			if (!almost_equal(lhs(i, j), rhs(i, j))) { return false; }
		}
	}
	return true;
}

bool operator!=(const Matrix &lhs, const Matrix &rhs) {
	return !(lhs == rhs);
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
	if (lhs._c != rhs._r) { throw std::invalid_argument("Number of columns of first matrix must equal number of rows of the second matrix"); }
	Matrix ret(lhs._r, rhs._c);
	for (int i = 0; i < ret._r; i++) {
		for (int j = 0; j < ret._c; j++) {
			ret(i, j) = dot(lhs, rhs, i, j);
		}
	}
	return ret;
}

Tuple operator*(const Matrix &lhs, const Tuple &rhs) {
	if (lhs._c != 4 || lhs._r != 4) { throw std::invalid_argument("Number of columns of matrix must equal 4 to multiple by a tuple"); }
	return Tuple(
		lhs(0, 0) * rhs._x + lhs(0, 1) * rhs._y + lhs(0, 2) * rhs._z + lhs(0, 3) * rhs._w,
		lhs(1, 0) * rhs._x + lhs(1, 1) * rhs._y + lhs(1, 2) * rhs._z + lhs(1, 3) * rhs._w,
		lhs(2, 0) * rhs._x + lhs(2, 1) * rhs._y + lhs(2, 2) * rhs._z + lhs(2, 3) * rhs._w,
		lhs(3, 0) * rhs._x + lhs(3, 1) * rhs._y + lhs(3, 2) * rhs._z + lhs(3, 3) * rhs._w);
}

Matrix identity_matrix(const int &size) {
	Matrix ret(size, size);
	for (int i = 0; i < size; i++) {
		ret(i, i) = 1.0;
	}
	return ret;
}

double dot(const Matrix& lhs, const Matrix& rhs, const int& row, const int& col) {
	if (lhs._c != rhs._r) { throw std::invalid_argument("Number of columns of first matrix must equal number of rows of the second matrix"); }
	double result = 0.0;
	for (int i = 0; i < lhs._c; i++) {
		result += lhs(row, i) * rhs(i, col);
	}
	return result;
}

Matrix transpose(const Matrix &m) {
	Matrix ret(m._r, m._c);
	for (int i = 0; i < ret._r; i++) {
		for (int j = 0; j < ret._c; j++) {
			ret(i, j) = m(j, i);
		}
	}
	return ret;
}

double determinant(const Matrix& m) {
	if ((m._r != m._c) || (m._r < 2) || (m._r > 4)) { throw std::invalid_argument("determinant matrix must be 2x2, 3x3 or 4x4"); }
	if (m._r == 2) { return ((m(0, 0) * m(1, 1)) - ((m(0, 1) * m(1, 0)))); }

	double det = 0.0;
	for (int i = 0; i < m._c; i++) {
		det += m(0, i) * cofactor(m, 0, i);
	}
	return det;
}

double cofactor(const Matrix& m, const int& elim_row, const int& elim_col) {
	if ((m._r != m._c) || (m._r < 3) || (m._r > 4)) { throw std::invalid_argument("cofactor parameter must be 3x3 or 4x4"); }
	Matrix temp = submatrix(m, elim_row, elim_col);
	return (((elim_row + elim_col) % 2 == 0) ? 1 : -1) * determinant(temp);
}

Matrix submatrix(const Matrix& m, const int& row_elim, const int& col_elim) {
	if ((m._r != m._c) || (m._r < 3) || (m._r > 4)) { throw std::invalid_argument("submatrix parameter must be 3x3 or 4x4"); }
	Matrix ret((m._r - 1), (m._c - 1));
	int offset_i = 0;
	int offset_j = 0;
	for (int i = 0; i < m._r; i++) {
		for (int j = 0; j < m._c; j++) {
			if (i == row_elim) {
				offset_i--;
				j = 0;
				break;
			}
			else if (j == col_elim) {
				offset_j--;
			}
			else {
				ret((i + offset_i), (j + offset_j)) = m(i, j);
			}
		}
		offset_j = 0;
	}
	return ret;
}

double minor(const Matrix& m, const int& elim_row, const int& elim_col) {
	if ((m._r != m._c) || (m._r < 3) || (m._r > 4)) { throw std::invalid_argument("minor parameter must be 3x3 or 4x4"); }
	return determinant(submatrix(m, elim_row, elim_col));
}

bool is_invertible(const Matrix& m) {
	return determinant(m) != 0;
}

Matrix inverse(const Matrix& m) {
	Matrix ret(m._r, m._c);
	double det = determinant(m);
	for (int i = 0; i < m._r; i++) {
		for (int j = 0; j < m._c; j++) {
			ret(j, i) = cofactor(m, i, j) / det;
		}
	}
	return ret;
}