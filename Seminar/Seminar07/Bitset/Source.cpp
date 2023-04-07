#include<iostream>
#pragma warning(disable : 4996)
#include"Bitset.h"

int main() {
	Bitset b(128);
	Bitset b1(10);

	b.addNumber(1);
	b.addNumber(2);
	b.addNumber(4);
	b.addNumber(8);
	b.addNumber(16);
	b.addNumber(32);
	b.addNumber(17);
	b.addNumber(128);


	b1.addNumber(1);
	b1.addNumber(3);
	b1.addNumber(5);
	b1.addNumber(7);
	b1.addNumber(9);

	Bitset u = b1.complement();

	u.addNumber(1000);

	for (size_t i = 0; i <= u.getMaxNumber(); i++)
		if (u.contains(i))
			std::cout << i << " ";
}