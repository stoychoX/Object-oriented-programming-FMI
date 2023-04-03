#include "Util.h"

bool isPrime(unsigned int num)
{
	bool isPrime = true;

	if (num == 0 || num == 1) {
		isPrime = false;
	}

	for (unsigned int i = 2; i <= num / 2; ++i) 
	{
		if (num % i == 0) 
		{
			isPrime = false;
			break;
		}
	}

	return isPrime;
}

bool isEven(unsigned int num)
{
	return !(num % 2);
}
bool isOdd(unsigned int num)
{
	return num % 2;
}
bool isPowerOfTwo(unsigned int num)
{
	return (num & (num - 1)) == 0;
}
bool guessNumber(unsigned int original, unsigned int num)
{
	return original == num;
}