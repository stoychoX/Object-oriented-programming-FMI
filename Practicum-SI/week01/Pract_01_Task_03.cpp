#include <iostream>
const size_t MAX_SIZE = 100;

struct pair
{
	int first;
	int second;
};

void readInput(pair& p)
{
	std::cin >> p.first;
	std::cin >> p.second;
}

bool comparePairs(const pair& p1, const pair& p2)
{
	return (p1.first > p2.first || (p1.first == p2.first && p1.second > p2.second));
}

pair findBiggestPair(const pair* array)
{
	pair biggestPair = { 0,0 };
	for (size_t i = 0; i < MAX_SIZE; i++)
	{
		if (comparePairs(array[i], biggestPair))
		{
			biggestPair = array[i];
		}
	}
	return biggestPair;
}

void selectionSort(pair* array, size_t N)
{
	for (size_t i = 0; i < N - 1; i++)
	{
		size_t minIndex = i;
		for (size_t j = 0; j < N; j++)
		{
			if (comparePairs(array[j], array[minIndex]))
			{
				minIndex = j;
			}
		}
		if (i != minIndex)
		{
			std::swap(array[i], array[minIndex]);
		}
	}
}
int main()
{
	pair p1;
	pair p2;
	readInput(p1);
	readInput(p2);

	pair arrayPairs[MAX_SIZE];
	for (size_t i = 0; i < MAX_SIZE; i++)
	{
		readInput(arrayPairs[i]);
	}
	size_t N;
	std::cin >> N;
	pair* arrayDynamic = new pair[N];
	for (size_t i = 0; i < N; i++)
	{
		readInput(arrayDynamic[i]);
	}
	pair biggestPair = findBiggestPair(arrayDynamic, N);
	std::cout << "(" << biggestPair.first << "," << biggestPair.second << ")";
	return 0;
}

//а се създаде структура, която 
//представлява наредена двойка от цели числа
//.Структурата има полета first и second.Да се реализират съответните функции :
//
//Функция, която прочита наредена двойка от стандартния вход
//Функция, която сравнява наредени двойки.Сравняването става по следния начин :
//(a, b) > (c, d) <=> (a > c) || ((a == c) && (b > d))
//Функция, която приема статичен масив от 100 наредени двойки и връща най - голямата наредена двойка.
//Функция, която приема динамичен масив от наредени двойки и ги сортира.