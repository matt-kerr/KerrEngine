// Matthew Kerr
#include "Matrix.h"
#include "KerrEngineException.h"

std::ostream& operator<<(std::ostream& out, const Matrix& m)
{
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			cout << m(i, j);
			if (j < m.cols - 1)
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	return out;
}

Matrix::Matrix()
{
	this->rows = 0;
	this->cols = 0;
	this->data = new double[0];
}

Matrix::Matrix(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
	this->data = new double[this->rows * this->cols];
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			(*this)(i, j) = 0.0;
		}
	}
}

Matrix::~Matrix() { delete [] data; }

// copy constructor
Matrix::Matrix(Matrix& orig)
{
	this->rows = orig.rows;
	this->cols = orig.cols;
	this->data = new double[this->rows * this->cols];
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			(*this)(i, j) = orig(i, j);
		}
	}
}

// move constructor
Matrix::Matrix(Matrix&& orig) noexcept
{
	this->rows = orig.rows;
	this->cols = orig.cols;
	this->data = new double[this->rows * this->cols];
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			(*this)(i, j) = orig(i, j);
		}
	}
}

// = operator overload
Matrix& Matrix::operator=(const Matrix& rhs)
{
	this->rows = rhs.rows;
	this->cols = rhs.cols;
	this->data = new double[this->rows * this->cols];
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			(*this)(i, j) = rhs(i, j);
		}
	}
	return *this;
}

// move = operator overload (move assignment overload)
Matrix& Matrix::operator=(Matrix&& orig)
{
	if (this != &orig)
	{
		this->rows = orig.rows;
		this->cols = orig.cols;
		this->data = new double[this->rows * this->cols];
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				(*this)(i, j) = orig(i, j);
			}
		}
	}
	return *this;
}

// == operator overload
bool Matrix::operator==(const Matrix& orig)
{
	if ((this->rows != orig.rows) || (this->cols != orig.cols))
	{
		return false;
	}
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			if ((*this)(i, j) != orig(i, j))
			{
				return false;
			}
		}
	}
	return true;
}

// [] writing overload (not allowed)
Matrix& Matrix::operator[](const int& index)
{
	throw KerrEngineException(EXCEPTION_MATRIX_NO_BRACKET_INDEX);
}

// [] reading overload (not allowed)
const Matrix& Matrix::operator[](const int& index) const
{
	throw KerrEngineException(EXCEPTION_MATRIX_NO_BRACKET_INDEX);
}

// m(x, y) writing overload
double& Matrix::operator()(const int& row, const int& col)
{
	if (row >= this->rows || col >= this->cols) { throw KerrEngineException(EXCEPTION_MATRIX_INDEX_OUT_OF_BOUNDS); }
	return data[(this->cols * row) + col];
}

// m(x, y) reading overload
double Matrix::operator()(const int& row, const int& col) const
{
	if (row >= this->rows || col >= this->cols) { throw KerrEngineException(EXCEPTION_MATRIX_INDEX_OUT_OF_BOUNDS); }
	return data[(this->cols * row) + col];
}

// Matrix + Matrix operator overload
Matrix Matrix::operator+(const Matrix& rhs) const
{
	if ((this->rows != rhs.rows) || (this->cols != rhs.cols))
	{
		throw KerrEngineException(EXCEPTION_MATRIX_ADDITION_NOT_SAME_SIZES);
	}
	Matrix result(this->rows, this->cols);
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			result(i, j) = (*this)(i, j) + rhs(i, j);
		}
	}
	return result;
}

// Matrix - Matrix operator overload
Matrix Matrix::operator-(const Matrix& rhs) const
{
	if ((this->rows != rhs.rows) || (this->cols !=rhs.cols))
	{
		throw KerrEngineException(EXCEPTION_MATRIX_ADDITION_NOT_SAME_SIZES);
	}
	Matrix result(this->rows, this->cols);
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			result(i, j) = (*this)(i, j) - rhs(i, j);
		}
	}
	return result;
}

// Matrix * Matrix operator overload
Matrix Matrix::operator*(const Matrix& rhs) const
{
	// Number of columns of first matrix must equal number of rows of the second matrix
	if (this->cols != rhs.rows)
	{
		throw KerrEngineException(EXCEPTION_MATRIX_MULTIPLICATION_INVALID_MATRIX_SIZES);
	}
	double temp;
	Matrix result(this->rows, rhs.cols);
	for (int i = 0; i < result.rows; i++)
	{
		for (int j = 0; j < result.cols; j++)
		{
			temp = this->dotProductMatrix(rhs, i, j);
			result(i, j) = abs(temp) < EPSILON ? 0.0 : temp;
		}
	}
	return result;
}

// Matrix * scalar operator overload
Matrix Matrix::operator*(const double& rhs) const
{
	Matrix result(this->rows, this->cols);
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			result(i, j) = (*this)(i, j) * rhs;
		}
	}
	return result;
}

// Matrix / scalar operator overload
Matrix Matrix::operator/(const double& rhs) const
{
	Matrix result(this->rows, this->cols);
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			result(i, j) = (*this)(i, j) / rhs;
		}
	}
	return result;
}

void Matrix::printPiValues()
{
	cout << "pi / 4 = " << std::numbers::pi / 4 << endl;
	cout << "pi / 2 = " << std::numbers::pi / 2 << endl;
	cout << "sqrt(2) / 2 = " << sqrt(2.0) / 2.0 << endl;
	cout << "----------" << endl;
}

void Matrix::vector(const double& x, const double& y, const double& z)
{
	this->resize(4, 1);
	(*this)(0, 0) = x;
	(*this)(1, 0) = y;
	(*this)(2, 0) = z;
	(*this)(3, 0) = 0.0;
}

void Matrix::point(const double& x, const double& y, const double& z)
{
	this->resize(4, 1);
	(*this)(0, 0) = x;
	(*this)(1, 0) = y;
	(*this)(2, 0) = z;
	(*this)(3, 0) = 1.0;
}

void Matrix::resize(const int& rows, const int& cols)
{
	this->rows = rows;
	this->cols = cols;
	delete [] this->data;
	this->data = new double[this->rows * this->cols];
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			(*this)(i, j) = 0.0;
		}
	}
}

void Matrix::identity(const int& size)
{
	this->rows = size;
	this->cols = size;
	delete[] this->data;
	this->data = new double[this->rows * this->cols];
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			if (i == j)
			{
				(*this)(i, j) = 1.0;
			}
			else
			{
				(*this)(i, j) = 0.0;
			}
		}
	}
}

void Matrix::transpose()
{
	Matrix temp(*this);
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			(*this)(i, j) = temp(j, i);
		}
	}
}

const double Matrix::dotProductMatrix(const Matrix& rhs, const int& row, const int& col) const
{
	// Number of columns of first matrix must equal number of rows of the second matrix
	if (this->cols != rhs.rows)
	{
		throw KerrEngineException(EXCEPTION_MATRIX_MULTIPLICATION_INVALID_MATRIX_SIZES);
	}
	double result = 0.0;
	for (int i = 0; i < this->cols; i++)
	{
		result += (*this)(row, i) * rhs(i, col);
	}
	return result;
}

const double Matrix::dotProductVector(const Matrix& rhs) const
{
	// Number of columns of first matrix must equal number of rows of the second matrix
	if (this->cols != 1 || this->rows != 4 || rhs.cols != 1 || rhs.rows != 4)
	{
		throw KerrEngineException(EXCEPTION_VECTOR_MULTIPLICATION_INVALID_MATRIX_SIZES);
	}
	
	return ((*this)(0, 0) * rhs(0, 0)) + ((*this)(1, 0) * rhs(1, 0)) + ((*this)(2, 0) * rhs(2, 0));
}

double Matrix::determinant()
{
	if ((this->rows != this->cols) || (this->rows < 2) || (this->rows > 4))
	{
		throw KerrEngineException(EXCEPTION_MATRIX_DETERMINANT_INVALID_MATRIX_SIZE);
	}
	else if (this->rows == 2 || this->cols == 2)
	{
		return ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(0, 1) * (*this)(1, 0));
	}
	else
	{
		double det = 0.0;
		for (int i = 0; i < this->cols; i++)
		{
			det += (*this)(0, i) * this->cofactor(0, i);
		}
		return det;
	}
}

double Matrix::minor(const int& elim_row, const int& elim_col)
{
	if (this->rows != this-> cols || this->rows < 3 || this->rows > 4)
	{
		throw KerrEngineException(EXCEPTION_MATRIX_MINOR_INVALID_MATRIX_SIZE);
	}
	Matrix temp;
	temp.becomeSubmatrix(*this, elim_row, elim_col);
	return temp.determinant();
}

double Matrix::cofactor(const int& elim_row, const int& elim_col)
{
	if (this->rows != this->cols || this->rows < 3 || this->rows > 4)
	{
		throw KerrEngineException(EXCEPTION_MATRIX_MINOR_INVALID_MATRIX_SIZE);
	}
	int cofactor_sign = ((elim_row + elim_col) % 2 == 0) ? 1 : -1;
	Matrix temp;
	temp.becomeSubmatrix(*this, elim_row, elim_col);
	return cofactor_sign * temp.determinant();
}

void Matrix::becomeSubmatrix(const Matrix& orig, const int& row_elim, const int& col_elim)
{
	if ((orig.rows != orig.cols) || (orig.rows < 3) || (orig.rows > 4))
	{
		throw KerrEngineException(EXCEPTION_SUBMATRIX_INVALID_SIZE);
	}
	this->resize(orig.rows - 1, orig.cols - 1);
	int offset_i = 0;
	int offset_j = 0;
	bool col_elim_happened = false;
	for (int i = 0; i < orig.rows; i++)
	{
		for (int j = 0; j < orig.cols; j++)
		{
			if (i == row_elim)
			{
				offset_i--;
				j = 0;
				break;
			} 
			else if (j == col_elim)
			{
				offset_j--;
			}
			else
			{
				(*this)((i + offset_i),(j + offset_j)) = orig(i ,j);
			}
		}
		offset_j = 0;
	}
}

bool Matrix::isInvertible()
{
	return this->determinant() != 0;
}

void Matrix::inverse()
{
	if (!this->isInvertible()) { throw KerrEngineException(EXCEPTION_MATRIX_NOT_INVERTIBLE); }
	
	Matrix temp(*this);
	double det = this->determinant();

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			(*this)(j, i) = temp.cofactor(i, j) / det;
		}
	}
}

void Matrix::translation(const double& x, const double& y, const double& z)
{
	this->identity(4);
	(*this)(0, 3) = x;
	(*this)(1, 3) = y;
	(*this)(2, 3) = z;
}

void Matrix::scaling(const double& x, const double& y, const double& z)
{
	this->identity(4);
	(*this)(0, 0) = x;
	(*this)(1, 1) = y;
	(*this)(2, 2) = z;
}

void Matrix::rotation_x(const double& r)
{
	(*this).identity(4);
	(*this)(1, 1) = cos(r);
	(*this)(1, 2) = sin(r) * -1.0;
	(*this)(2, 1) = sin(r);
	(*this)(2, 2) = cos(r);
}

void Matrix::rotation_y(const double& r)
{
	(*this).identity(4);
	(*this)(0, 0) = cos(r);
	(*this)(0, 2) = sin(r);
	(*this)(2, 0) = sin(r) * -1.0;
	(*this)(2, 2) = cos(r);
}

void Matrix::rotation_z(const double& r)
{
	(*this).identity(4);
	(*this)(0, 0) = cos(r);
	(*this)(0, 1) = sin(r) * -1.0;
	(*this)(1, 0) = sin(r);
	(*this)(1, 1) = cos(r);
}

void Matrix::shearing(const double& x_y, const double& x_z, const double& y_x, const double& y_z, const double& z_x, const double& z_y)
{
	(*this).identity(4);
	(*this)(0, 1) = x_y;
	(*this)(0, 2) = x_z;
	(*this)(1, 0) = y_x;
	(*this)(1, 2) = y_z;
	(*this)(2, 0) = z_x;
	(*this)(2, 1) = z_y;
}

Matrix Matrix::normalize()
{
	if (this->rows != 4 || this->cols != 1 || (*this)(3, 0) != 0) { throw KerrEngineException(EXCEPTION_ATTEMPTED_NORMALIZE_NON_VECTOR); }
	Matrix result;
	double magnitude;
	magnitude = this->magnitude();
	result.point(((*this)(0, 0) / magnitude), ((*this)(1, 0) / magnitude), ((*this)(2, 0) / magnitude));
	return result;
}

// Calculates the length of a vector.
double Matrix::magnitude()
{
	if (this->rows != 4 || this->cols != 1 || (*this)(3, 0) != 0) { throw KerrEngineException(EXCEPTION_ATTEMPTED_MAGNITUDE_NON_VECTOR); }
	return sqrt(pow((*this)(0, 0), 2) + pow((*this)(1, 0), 2) + pow((*this)(2, 0), 2));
}