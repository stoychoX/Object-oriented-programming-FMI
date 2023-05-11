#pragma once
#include <fstream>

class Matrix
{
private:
	int** matrix = nullptr;
	unsigned n = 0;
	unsigned m = 0;

	void copyFrom(const Matrix& other);
	void free();
public:
	Matrix();
	Matrix(const int** matrix, unsigned n, unsigned m);
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	~Matrix();

	int** getMatrix() const;
	unsigned getRowsCount() const;
	unsigned getColsCount() const;

	void setMatrix(const int** matrix, unsigned n, unsigned m);

	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);

	friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
	friend std::istream& operator>>(std::istream& is, Matrix& matrix);
};