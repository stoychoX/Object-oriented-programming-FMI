#include<iostream>
#include"SubsetIter.h"

int main() {
	int* arr = new int[4];

	for (size_t i = 0; i < 4; i++)
		arr[i] = i;

	SubsetIter s(arr, 4);

	while (true) {
		std::cout << s;
		++s;
		std::cin.get();
	}

	delete[] arr;
}