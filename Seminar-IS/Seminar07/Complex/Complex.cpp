#include "Complex.h"

Complex::Complex() : Complex(0, 0) {}

Complex::Complex(double re, double im) : re(re), im(im) {}

Complex Complex::getConjugate() const
{
    return Complex(re, -im);
}

Complex& Complex::operator+=(const Complex& other)
{
    re += other.re;
    im += other.im;

    return *this;
}

Complex& Complex::operator-=(const Complex& other)
{
    re -= other.re;
    im -= other.im;

    return *this;
}

Complex& Complex::operator*=(const Complex& other)
{
    double oldRe = re;
    re = re * other.re - im * other.im;
    im = oldRe * other.im + im * other.re;
    
    return *this;
}

Complex& Complex::operator/=(const Complex& other)
{
	Complex Conjugated = other.getConjugate();

	Complex otherCopy(other);

	*this *= Conjugated;
	otherCopy *= Conjugated;

	if (otherCopy.re != 0)
	{
		re /= otherCopy.re;
		im /= otherCopy.re;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Complex& other)
{
    return os << other.re << " " << other.im << std::endl;
}

Complex operator+(const Complex& lhs, const Complex& rhs)
{
    Complex toReturn(lhs);
    toReturn += rhs;
    return toReturn;
}

Complex operator-(const Complex& lhs, const Complex& rhs)
{
    Complex toReturn(lhs);
    toReturn -= rhs;
    return toReturn;
}

Complex operator*(const Complex& lhs, const Complex& rhs)
{
    Complex toReturn(lhs);
    toReturn *= rhs;
    return toReturn;
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    Complex toReturn(lhs);
    toReturn /= rhs;
    return toReturn;
}
