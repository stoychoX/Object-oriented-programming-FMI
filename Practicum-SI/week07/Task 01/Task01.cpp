#include <iostream>
#include "Matrix.h"
#pragma warning (disable : 4996)

int main()
{
	Matrix matrix1(nullptr, 2, 3);
	int* arr1 = new int[3] {1, 2, 3};
	int* arr2 = new int[3] {4, 2, 33};
	int* arr3 = new int[3] {5, 0, 2};


	const int** arr = new const int* [3];
	arr[0] = arr1;
	arr[1] = arr2;
	arr[2] = arr3;
	matrix1.setMatrix(arr, 3, 3);
	std::cout << matrix1;

	Matrix a;
	std::cout << a;
}

