#include <iostream>
#include <fstream>

int CharCount(const char* fileName, char ch1, char ch2)
{
	std::ifstream myFile(fileName);
	if (!myFile.is_open())
		return -1;

	int counter = 0;
	char c;
	while (true)
	{
		c = myFile.get();
		if (myFile.eof())
			break;

		if (c != ch1 && c != ch2)
		{
			counter++;
		}
	}
	return counter;
}

int main()
{
	std::cout << CharCount("task02_test.txt", 'a', 'd');
}