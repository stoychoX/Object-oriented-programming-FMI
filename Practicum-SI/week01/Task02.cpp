#include <iostream>

int GetCountNumbersWithBetterASCII(int* nums, int len, char symbol)
{
	if (nums == nullptr)
	{
		return 0;
	}
	int countNums = 0;
	for (int i = 0; i < len; i++)
	{
		if (nums[i] > symbol)
		{
			countNums++;
		}
	}
	return countNums;
}

int main()
{
	int N;
	std::cin >> N;
	int* numbers = new int[N];
	for (int i = 0; i < N; i++)
	{
		std::cin >> numbers[i];
	}
	char symbol;
	std::cin >> symbol;
	std::cout << GetCountNumbersWithBetterASCII(numbers, N, symbol);
	delete[] numbers;
}
