#include <iostream>

struct Rational 
{
    int64_t numerator;
    int64_t denominator;
};

int64_t gcd(int64_t a, int64_t b)
{
    a = std::abs(a);
    b = std::abs(b);

    if(b == 0)
        return a;
    
    return gcd(b, a % b);
}

void canonicalizeNumber(Rational& r)
{
    int64_t greatestCommonDivisor = gcd(r.numerator, r.denominator);
    r.numerator /= greatestCommonDivisor;
    r.denominator /= greatestCommonDivisor;

    if(r.numerator < 0 && r.denominator < 0)
    {
        r.numerator *= -1;
        r.denominator *= -1;
    }
}

Rational createRational(int64_t num, int64_t denom)
{
    if(!denom) 
        denom = 1;

    Rational toReturn = { num, denom };
    canonicalizeNumber(toReturn);

    return toReturn;
}

Rational sum(const Rational& lhs, const Rational& rhs)
{
    return createRational(
        lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator, 
        lhs.denominator * rhs.denominator
    );
}

Rational negative(const Rational& r)
{
    return createRational(-1 * r.numerator, r.denominator);
}

Rational subtract(const Rational& lhs, const Rational& rhs)
{
    return sum(lhs, negative(rhs));
}

Rational multiply(const Rational& lhs, const Rational& rhs)
{
    return createRational(
        lhs.numerator * rhs.numerator,
        lhs.denominator * rhs.denominator
    );
}

Rational divide(const Rational& lhs, const Rational& rhs)
{    
    return multiply(lhs, createRational(rhs.denominator, rhs.numerator));
}

void printRational(const Rational& r)
{
    std::cout << r.numerator;

    if (r.denominator != 1) {
        std::cout << '/' << r.denominator;
    }

    std::cout << std::endl;
}

int main()
{
    Rational first = createRational(7, 2);
    Rational second = createRational(3, 4);

    Rational sumRes = sum(first, second);
    Rational subtractRes = subtract(first, second);
    Rational multiplyRes = multiply(first, second);
    Rational divideRes = divide(first, second);

    printRational(sumRes);
    printRational(subtractRes);
    printRational(multiplyRes);
    printRational(divideRes);
}