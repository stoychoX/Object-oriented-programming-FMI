#include "Matrix.h"

namespace
{
	void fillRow(int* rowDest, const int* rowSrc, unsigned length)
	{
		for (size_t i = 0; i < length; i++)
		{
			rowDest[i] = rowSrc[i];
		}
	}
}

void Matrix::copyFrom(const Matrix& other)
{
	this->n = other.n;
	this->m = other.m;

	this->matrix = new int* [n];
	for (size_t i = 0; i < n; i++)
	{
		this->matrix[i] = new int[m];
		fillRow(matrix[i], other.getMatrix()[i], m);
	}
}

void Matrix::free()
{
	for (size_t i = 0; i < getRowsCount(); i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

Matrix::Matrix()//create a matrix 1 by 1 with value 0
{
	n = m = 1;
	matrix = new int* [1];
	matrix[0] = new int[1];
	matrix[0][0] = 0;
}

Matrix::Matrix(const int** matrix, unsigned n, unsigned m)
{
	if (matrix == nullptr)
	{
		this->n = n;
		this->m = m;
		this->matrix = new int* [n];
		for (size_t i = 0; i < n; i++)
		{
			this->matrix[i] = new int[m];
			for (size_t j = 0; j < m; j++)
			{
				this->matrix[i][j] = 0;
			}
		}
		return;
	}
	setMatrix(matrix, n, m);
}

Matrix::Matrix(const Matrix& other)
{
	copyFrom(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Matrix::~Matrix()
{
	free();
}

int** Matrix::getMatrix() const
{
	return matrix;
}

unsigned Matrix::getRowsCount() const
{
	return n;
}

unsigned Matrix::getColsCount() const
{
	return m;
}

void Matrix::setMatrix(const int** matrix, unsigned n, unsigned m)
{
	if (matrix == nullptr)
	{
		throw "Error";
	}
	for (size_t i = 0; i < n; i++)
	{
		if (matrix[i] == nullptr)
		{
			throw "Error";
		}
	}
	free();
	//is that good or use the following:
	//Matrix matrixNew(matrix, n ,m);
	//copyFrom(matrixNew);
	this->n = n;
	this->m = m;
	this->matrix = new int* [n];
	for (size_t i = 0; i < n; i++)
	{
		this->matrix[i] = new int[m];
		fillRow(this->matrix[i], matrix[i], m);
	}
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	if (n != other.getRowsCount() || m != other.getColsCount())
	{
		throw "Error";
	}
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			matrix[i][j] += other.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	if (n != other.getRowsCount() || m != other.getColsCount())
	{
		throw "Error";
	}
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			matrix[i][j] -= other.matrix[i][j];
		}
	}return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	if (m != other.getRowsCount())
	{
		throw "Error";
	}
	Matrix matrixMult(nullptr, n, other.getColsCount());

	for (size_t j = 0; j < n; j++)
	{
		for (size_t i = 0; i < other.getColsCount(); i++)
		{
			int value = 0;
			for (size_t k = 0; k < m; k++)
			{
				value += matrix[j][k] * other.matrix[k][i];
			}
			matrixMult.matrix[j][i] = value;
		}
	}

	free();
	n = matrixMult.getRowsCount();
	m = matrixMult.getColsCount(); 
	this->matrix = new int*[n];
	for (size_t i = 0; i < n; i++)
	{
		this->matrix[i] = new int[m];
		for (size_t j = 0; j < m; j++)
		{
			fillRow(this->matrix[i], matrixMult.getMatrix()[i], m);
		}
	}
	return *this;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	Matrix matrix(lhs);
	matrix += rhs;
	return matrix;

}

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
	Matrix matrix(lhs);
	matrix -= rhs;
	return matrix;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
	Matrix matrix(lhs);
	matrix *= rhs;
	return matrix;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
	for (size_t i = 0; i < matrix.getRowsCount(); i++)
	{
		for (size_t j = 0; j < matrix.getColsCount(); j++)
		{
			os << matrix.getMatrix()[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Matrix& matrix)
{
	for (size_t i = 0; i < matrix.getRowsCount(); i++)
	{
		for (size_t j = 0; j < matrix.getColsCount(); j++)
		{
			is >> matrix.matrix[i][j];
		}
	}
	return is;
}
