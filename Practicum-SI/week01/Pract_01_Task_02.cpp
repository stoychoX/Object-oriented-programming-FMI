#include <iostream>

void readArr(size_t* arr, size_t N)
{
	for (size_t i = 0; i < N; i++)
	{
		std::cin >> arr[i];
	}
}

size_t findCount(const size_t* arr, char symbol, size_t N)
{
	size_t counter = 0;
	for (size_t i = 0; i < N; i++)
	{
		if (arr[i] > symbol)
		{
			counter++;
		}
	}
	return counter;

}

int main()
{
	size_t N;
	std::cin >> N;
	size_t* arrNums = new size_t[N];
	readArr(arrNums, N);
	char symbol;
	std::cin >> symbol;
	std::cout << findCount(arrNums, symbol, N);
	delete[]arrNums;
	return 0;
}

//Прочетете цяло число N от стандартния вход, последвано 
//от N на брой цели числа.
//Прочетете един символ от стандартния вход.
//Намерете броя на тези цели числа
//от въведените, които са по - големи от ASCII кода на символа.
//За целта използвайте динамична памет и функции.