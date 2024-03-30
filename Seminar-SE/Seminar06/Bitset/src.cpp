#include "Bitset.h"

int main()
{
	Bitset powersOfTwo(17);
	powersOfTwo.addNumber(1);
	powersOfTwo.addNumber(2);
	powersOfTwo.addNumber(4);
	powersOfTwo.addNumber(8);
	powersOfTwo.addNumber(16);

	Bitset even(17);
	for (size_t i = 0; i < 17; i += 2)
		even.addNumber(i);

	powersOfTwo.print();
	even.print();

	Bitset evenPowerUnion = powersOfTwo.Union(even);
	evenPowerUnion.print();

	Bitset evenPowerIntersect = powersOfTwo.Intersect(even);
	evenPowerIntersect.print();

	powersOfTwo.removeNumber(1);
	powersOfTwo.removeNumber(16);
	powersOfTwo.print();
} 