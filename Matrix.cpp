// Matthew Kerr
#include "Matrix.h"
#include "KerrEngineException.h"

std::ostream& operator<<(std::ostream& out, const Matrix& m)
{
	if (m.type == "VECTOR")
	{
		cout << "vector(" << m(0, 0) << ", " << m(1, 0) << ", " << m(2, 0) << ", " << m(3, 0) << ")" << endl;
	}
	else if (m.type == "POINT")
	{
		cout << "point(" << m(0, 0) << ", " << m(1, 0) << ", " << m(2, 0) << ", " << m(3, 0) << ")" << endl;
	}
	else
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
	}
	return out;
}

Matrix::Matrix()
{
	this->rows = 0;
	this->cols = 0;
	this->type = "MATRIX";
	this->data = new double[0];
}

Matrix::Matrix(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
	this->type = "MATRIX";
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
	this->type = orig.type;
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
	this->type = orig.type;
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
	this->type = rhs.type;
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
		this->type = orig.type;
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
bool Matrix::operator==(const Matrix& rhs)
{
	if ((this->rows != rhs.rows) || (this->cols != rhs.cols) || (this->type != rhs.type))
	{
		return false;
	}
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			if ((*this)(i, j) != rhs(i, j))
			{
				return false;
			}
		}
	}
	return true;
}

Matrix Matrix::operator-() const
{
	Matrix ret(this->rows, this->cols);
	ret.data = new double[ret.rows * ret.cols];
	ret.type = this->type;
	for (int i = 0; i < ret.rows; i++)
	{
		for (int j = 0; j < ret.cols; j++)
		{
			ret(i, j) = (*this)(i, j) * -1.0;
		}
	}
	if (this->type == "VECTOR" || this->type == "POINT") { ret(3, 0) = (*this)(3, 0); }
	return ret;
}

// [] writing overload (not allowed)
Matrix& Matrix::operator[](const int& index)
{
	throw KerrEngineException("EXCEPTION_MATRIX_NO_BRACKET_INDEX");
}

// [] reading overload (not allowed)
const Matrix& Matrix::operator[](const int& index) const
{
	throw KerrEngineException("EXCEPTION_MATRIX_NO_BRACKET_INDEX");
}

// m(x, y) writing overload
double& Matrix::operator()(const int& row, const int& col)
{
	if (row >= this->rows || col >= this->cols) { throw KerrEngineException("EXCEPTION_MATRIX_INDEX_OUT_OF_BOUNDS"); }
	return data[(this->cols * row) + col];
}

// m(x, y) reading overload
double Matrix::operator()(const int& row, const int& col) const
{
	if (row >= this->rows || col >= this->cols) { throw KerrEngineException("EXCEPTION_MATRIX_INDEX_OUT_OF_BOUNDS"); }
	return data[(this->cols * row) + col];
}

// Matrix + Matrix operator overload
Matrix Matrix::operator+(const Matrix& rhs) const
{
	if (this->type == "POINT" && rhs.type == "POINT") { throw KerrEngineException("EXCEPTION_CANNOT_ADD_TWO_POINTS"); }
	if ((this->rows != rhs.rows) || (this->cols != rhs.cols)) { throw KerrEngineException("EXCEPTION_MATRIX_ADDITION_NOT_SAME_SIZES"); }
	Matrix ret(this->rows, this->cols);
	ret.data = new double[ret.rows * ret.cols];
	double temp;
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			temp = (*this)(i, j) + rhs(i, j);
			ret(i, j) = abs(temp) < EPSILON ? 0.0 : temp;
		}
	}
	if (this->type == "VECTOR" && rhs.type == "VECTOR") { ret.type = "VECTOR"; }
	if (this->type == "VECTOR" && rhs.type == "POINT") { ret.type = "POINT"; }
	if (this->type == "POINT" && rhs.type == "VECTOR") { ret.type = "POINT"; }
	return ret;
}

// Matrix - Matrix operator overload
Matrix Matrix::operator-(const Matrix& rhs) const
{
	if (this->type == "VECTOR" && rhs.type == "POINT") { throw KerrEngineException("EXCEPTION_CANNOT_SUBTRACT_POINT_FROM_VECTOR"); }
	if ((this->rows != rhs.rows) || (this->cols !=rhs.cols)) { throw KerrEngineException("EXCEPTION_MATRIX_ADDITION_NOT_SAME_SIZES"); }
	Matrix ret(this->rows, this->cols);
	ret.data = new double[ret.rows * ret.cols];
	double temp;
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			temp = (*this)(i, j) - rhs(i, j);
			ret(i, j) = abs(temp) < EPSILON ? 0.0 : temp;
		}
	}
	if (this->type == "VECTOR" && rhs.type == "VECTOR") { ret.type = "VECTOR"; }
	if (this->type == "POINT" && rhs.type == "POINT") { ret.type = "VECTOR"; }
	if (this->type == "POINT" && rhs.type == "VECTOR") { ret.type = "POINT"; }
	return ret;
}

// Matrix * Matrix operator overload
Matrix Matrix::operator*(const Matrix& rhs) const
{
	// Number of columns of first matrix must equal number of rows of the second matrix
	if (this->cols != rhs.rows)
	{
		throw KerrEngineException("EXCEPTION_MATRIX_MULTIPLICATION_INVALID_MATRIX_SIZES");
	}
	double temp;
	Matrix ret(this->rows, rhs.cols);
	ret.data = new double[ret.rows * ret.cols];
	ret.type = rhs.type;
	for (int i = 0; i < ret.rows; i++)
	{
		for (int j = 0; j < ret.cols; j++)
		{
			temp = Matrix::dot((*this), rhs, i, j);
			ret(i, j) = abs(temp) < EPSILON ? 0.0 : temp;
		}
	}
	
	return ret;
}

// Matrix * scalar operator overload
Matrix Matrix::operator*(const double& rhs) const
{
	Matrix ret(this->rows, this->cols);
	ret.type = this->type;
	ret.data = new double[ret.rows * ret.cols];
	double temp;
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			temp = (*this)(i, j) * rhs;
			ret(i, j) = abs(temp) < EPSILON ? 0.0 : temp;
		}
	}
	if (this->type == "VECTOR" || this->type == "POINT") { ret(3, 0) = (*this)(3, 0); }
	return ret;
}

// Matrix / scalar operator overload
Matrix Matrix::operator/(const double& rhs) const
{
	Matrix ret(this->rows, this->cols);
	ret.type = this->type;
	ret.data = new double[ret.rows * ret.cols];
	double temp;
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			temp = (*this)(i, j) / rhs;
			ret(i, j) = abs(temp) < EPSILON ? 0.0 : temp; 
		}
	}
	if (this->type == "VECTOR" || this->type == "POINT") { ret(3, 0) = (*this)(3, 0); }
	return ret;
}

void Matrix::printPiValues()
{
	cout << "pi / 4 = " << std::numbers::pi / 4 << endl;
	cout << "pi / 2 = " << std::numbers::pi / 2 << endl;
	cout << "sqrt(2) / 2 = " << sqrt(2.0) / 2.0 << endl;
	cout << "----------" << endl;
}

Matrix Matrix::submatrix(const Matrix& m, const int& row_elim, const int& col_elim)
{
	if ((m.rows != m.cols) || (m.rows < 3) || (m.rows > 4)) { throw KerrEngineException("EXCEPTION_SUBMATRIX_INVALID_SIZE"); }
	Matrix ret((m.rows - 1), (m.cols - 1));
	int offset_i = 0;
	int offset_j = 0;
	bool col_elim_happened = false;
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
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
				ret((i + offset_i), (j + offset_j)) = m(i, j);
			}
		}
		offset_j = 0;
	}
	return ret;
}

// vector mode only
Matrix Matrix::normalize(const Matrix& m)
{
	if (m.type != "VECTOR") { throw KerrEngineException("EXCEPTION_ATTEMPTED_NORMALIZE_NON_VECTOR"); }
	double magnitude = Matrix::magnitude(m);
	return Matrix::vector((m(0, 0) / magnitude), (m(1, 0) / magnitude), (m(2, 0) / magnitude));
}

Matrix Matrix::identity(const int& size)
{
	Matrix ret(size, size);
	ret.data = new double[ret.rows * ret.cols];
	for (int i = 0; i < ret.rows; i++)
	{
		for (int j = 0; j < ret.cols; j++)
		{
			if (i == j) { ret(i, j) = 1.0; }
			else { ret(i, j) = 0.0; }
		}
	}
	return ret;
}

Matrix Matrix::transpose(const Matrix& m)
{
	Matrix ret(m.rows, m.cols);
	for (int i = 0; i < ret.rows; i++)
	{
		for (int j = 0; j < ret.cols; j++)
		{
			ret(i, j) = m(j, i);
		}
	}
	return ret;
}

bool Matrix::isInvertible(const Matrix& m)
{
	return Matrix::determinant(m) != 0;
}

Matrix Matrix::inverse(const Matrix& m)
{
	if (!Matrix::isInvertible(m)) { throw KerrEngineException("EXCEPTION_MATRIX_NOT_INVERTIBLE"); }
	Matrix ret(m.rows, m.cols);
	double det = Matrix::determinant(m);

	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			ret(j, i) = Matrix::cofactor(m, i, j) / det;
		}
	}
	return ret;
}

Matrix Matrix::vector(const double& x, const double& y, const double& z)
{
	Matrix ret(4, 1);
	ret.type = "VECTOR";
	ret(0, 0) = x;
	ret(1, 0) = y;
	ret(2, 0) = z;
	ret(3, 0) = 0.0;
	return ret;
}

Matrix Matrix::point(const double& x, const double& y, const double& z)
{
	Matrix ret(4, 1);
	ret.type = "POINT";
	ret(0, 0) = x;
	ret(1, 0) = y;
	ret(2, 0) = z;
	ret(3, 0) = 1.0;
	return ret;
}

Matrix Matrix::translation(const double& x, const double& y, const double& z)
{
	Matrix ret = Matrix::identity(4);
	ret(0, 3) = x;
	ret(1, 3) = y;
	ret(2, 3) = z;
	return ret;
}

Matrix Matrix::scaling(const double& x, const double& y, const double& z)
{
	Matrix ret = Matrix::identity(4);
	ret(0, 0) = x;
	ret(1, 1) = y;
	ret(2, 2) = z;
	return ret;
}

Matrix Matrix::rotationX(const double& r)
{
	Matrix ret = Matrix::identity(4);
	ret(1, 1) = cos(r);
	ret(1, 2) = sin(r) * -1.0;
	ret(2, 1) = sin(r);
	ret(2, 2) = cos(r);
	return ret;
}

Matrix Matrix::rotationY(const double& r)
{
	Matrix ret = Matrix::identity(4);
	ret(0, 0) = cos(r);
	ret(0, 2) = sin(r);
	ret(2, 0) = sin(r) * -1.0;
	ret(2, 2) = cos(r);
	return ret;
}


Matrix Matrix::rotationZ(const double& r)
{
	Matrix ret = Matrix::identity(4);
	ret(0, 0) = cos(r);
	ret(0, 1) = sin(r) * -1.0;
	ret(1, 0) = sin(r);
	ret(1, 1) = cos(r);
	return ret;
}

Matrix Matrix::shearing(const double& x_y, const double& x_z, const double& y_x, const double& y_z, const double& z_x, const double& z_y)
{
	Matrix ret = Matrix::identity(4);
	ret(0, 1) = x_y;
	ret(0, 2) = x_z;
	ret(1, 0) = y_x;
	ret(1, 2) = y_z;
	ret(2, 0) = z_x;
	ret(2, 1) = z_y;
	return ret;
}

Matrix Matrix::cross(const Matrix& lhs, const Matrix& rhs)
{
	// Check that both are vectors
	if (lhs.type != "VECTOR" || rhs.type != "VECTOR") { throw KerrEngineException("EXCEPTION_DOT_PRODUCT_NOT_VECTORS"); }
	return Matrix::vector(
		(lhs(1, 0) * rhs(2, 0)) - (lhs(2, 0) * rhs(1, 0))
		, (lhs(2, 0) * rhs(0, 0)) - (lhs(0, 0) * rhs(2, 0))
		, (lhs(0, 0) * rhs(1, 0)) - (lhs(1, 0) * rhs(0, 0)));
}

// vector
double Matrix::dot(const Matrix& lhs, const Matrix& rhs)
{
	// Check that both are vectors
	if (lhs.type != "VECTOR" || rhs.type != "VECTOR") { throw KerrEngineException("EXCEPTION_ATTEMPTED_DOT_PRODUCT_USING_NON_VECTORS"); }
	return ((lhs(0, 0) * rhs(0, 0)) + (lhs(1, 0) * rhs(1, 0)) + (lhs(2, 0) * rhs(2, 0)));
}

// matrix
double Matrix::dot(const Matrix& lhs, const Matrix& rhs, const int& row, const int& col)
{
	// Number of columns of first matrix must equal number of rows of the second matrix
	if (lhs.cols != rhs.rows)
	{
		throw KerrEngineException("EXCEPTION_MATRIX_MULTIPLICATION_INVALID_MATRIX_SIZES");
	}
	double result = 0.0;
	for (int i = 0; i < lhs.cols; i++)
	{
		result += lhs(row, i) * rhs(i, col);
	}
	return result;
}



double Matrix::determinant(const Matrix& m)
{
	if ((m.rows != m.cols) || (m.rows < 2) || (m.rows > 4)) { throw KerrEngineException("EXCEPTION_MATRIX_DETERMINANT_INVALID_MATRIX_SIZE"); }
	else if (m.rows == 2 || m.cols == 2)
	{
		return (m(0, 0) * m(1, 1)) - (m(0, 1) * m(1, 0));
	}
	else
	{
		double det = 0.0;
		for (int i = 0; i < m.cols; i++)
		{
			det += m(0, i) * Matrix::cofactor(m, 0, i);
		}
		return det;
	}
}

double Matrix::minor(const Matrix& m, const int& elim_row, const int& elim_col)
{
	if ((m.rows != m.cols) || (m.rows < 3) || (m.rows > 4)) { throw KerrEngineException("EXCEPTION_MATRIX_MINOR_INVALID_MATRIX_SIZE"); }
	return Matrix::determinant(Matrix::submatrix(m, elim_row, elim_col));
}

double Matrix::cofactor(const Matrix& m, const int& elim_row, const int& elim_col)
{
	if ((m.rows != m.cols) || (m.rows < 3) || (m.rows > 4)) { throw KerrEngineException("EXCEPTION_MATRIX_MINOR_INVALID_MATRIX_SIZE"); }
	Matrix temp = Matrix::submatrix(m, elim_row, elim_col);
	return (((elim_row + elim_col) % 2 == 0) ? 1 : -1) * Matrix::determinant(temp);
}

// calculates the length of a vector
double Matrix::magnitude(const Matrix& m)
{
	if (m.type != "VECTOR") { throw KerrEngineException("EXCEPTION_ATTEMPTED_MAGNITUDE_NON_VECTOR"); }
	return sqrt(pow(m(0, 0), 2) + pow(m(1, 0), 2) + pow(m(2, 0), 2));
}

// vector mode only
Matrix Matrix::reflect(const Matrix& in, const Matrix& normal)
{
	if (in.type != "VECTOR" || normal.type != "VECTOR") { throw KerrEngineException("EXCEPTION_ATTEMPTED_REFLECT_NON_VECTOR"); }
	return in - normal * 2 * Matrix::dot(in, normal);
}