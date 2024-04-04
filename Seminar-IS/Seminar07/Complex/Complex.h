#pragma once
#include <iostream>
class Complex
{
private:
	double re;
	double im;
public:
	Complex();
	Complex(double re, double im);

	Complex getConjugate() const;

	Complex& operator+=(const Complex& other);
	Complex& operator-=(const Complex& other);
	Complex& operator*=(const Complex& other);
	Complex& operator/=(const Complex& other);

	friend std::ostream& operator<<(std::ostream& os, const Complex& other);
};

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const Complex& rhs);