#include <iostream>

void SwapVar(int* arr, int j, int temp = 0)
{
	temp = arr[j - 1];
	arr[j - 1] = arr[j];
	arr[j] = temp;
}

void ChekingForSwap(int* arr, int j)
{
	if (arr[j - 1] < arr[j])
	{
		SwapVar(arr, j);
	}
}

void BubbleSort(int* arr, int n)
{
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < n; j++)
		{
			ChekingForSwap(arr, j);
		}
	}
}

int CounterNumberBiggerThanASCII(int* arr, char ch, int n, int index = 0)
{
	BubbleSort(arr, n);
	while (arr[index] > ch)
	{
		index++;
	}
	return index;
}

void InputArray(int* arr, size_t n)
{
	for (int i = 0; i < n; i++)
	{
		std::cin >> arr[i];
	}
}

void InputChar(char& ch)
{
	std::cin >> ch;
}

void HowManyNumbersBiggerThanASCII(int* arr, char ch, int n)
{
	InputArray(arr, n);
	InputChar(ch);
	std::cout << CounterNumberBiggerThanASCII(arr, ch, n);
}

int main()
{
	int n = 0;
	char ch = ' ';
	std::cin >> n;
	int* arr = new int[n];
	HowManyNumbersBiggerThanASCII(arr, ch, n);
	delete[] arr;
}
