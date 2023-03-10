#include <iostream>

int countSymbols(const char* arr, int len, char ch)
{
	int counter = 0;
	for (int i = 0; i < len; i++)
	{
		if ((int)arr[i] > (int)ch)
		{
			counter++;
		}
	}
	return counter;
}

void readArray(char* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		std::cin >> arr[i];
	}
}

int main()
{
	int n;
	std::cin >> n;
	char* string = new char[n];
	readArray(string, n);
	char ch;
	std::cin >> ch;
	std::cout<<countSymbols(string, n, ch);
	delete[] string;
}