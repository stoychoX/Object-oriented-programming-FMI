#include <iostream>
#include <fstream>

int main()
{
	std::ifstream myFile("file.txt");

	if (!myFile.is_open())
	{
		return -1;
	}

	int counter = 0;
	while (true)
	{
		char current = myFile.get();
		if (myFile.eof())
			break;

		if (current != 'a' && current != 'd')
			counter++;
	}

	std::cout << counter;

	myFile.close();
}