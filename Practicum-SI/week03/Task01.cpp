#include <iostream>
#include <fstream>

struct Example {
	int data;
	char buff[8];
};

Example readExample()
{
	Example ex;
	std::cin >> ex.data;
	std::cin >> ex.buff;
	return ex;
}

void writeExampleIntoFile(const Example& ex, std::ofstream& ofs)
{
	if (!ofs.is_open())
	{
		return;
	}
	ofs << ex.data << " " << ex.buff << std::endl;
}

int main()
{
	int n;
	std::cin >> n;
	Example* examples = new Example[n];
	for (size_t i = 0; i < n; i++)
	{
		examples[i] = readExample();
	}
	char nameOfFile[20];
	std::cin >> nameOfFile;
	std::ofstream ofs(nameOfFile, std::ios::app);
	if (!ofs.is_open())
	{
		std::cout << "File not found!";
		delete[] examples;
		return -1;
	}
	for (size_t i = 0; i < n; i++)
	{
		writeExampleIntoFile(examples[i], ofs);
	}
	ofs.close();
	delete[] examples;
}

