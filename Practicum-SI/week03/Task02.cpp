#include <iostream>
#include <fstream>
#pragma warning(disable::4996)

struct Example {
	int data;
	char buff[8];
};

Example readExampleFromFile(std::ifstream& ifs)
{
	Example ex{ -1, "err" };
	if (ifs.is_open())
	{
		ifs.read((char*)&ex.data, sizeof(ex.data));
		ifs.read(ex.buff, 8);
	}
	return ex;

}

void writeExample(const Example& ex, std::ofstream& ofs)
{
	if (!ofs.is_open())
	{
		return;
	}
	ofs.write((const char*)&ex.data, sizeof(ex.data));
	ofs.write(ex.buff, 8);
}

size_t getFileSize(std::ifstream& ifs)
{
	if (!ifs.is_open())
	{
		return  0;
	}
	unsigned currPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	unsigned size = ifs.tellg();
	ifs.seekg(currPos);
	ifs.clear();
	return size;
}

size_t examplesInFile(const char* filePath)
{
	std::ifstream ifs(filePath, std::ios::binary);
	if (!ifs.is_open())
	{
		return 0;
	}
	unsigned fileSize = getFileSize(ifs);
	return (fileSize / sizeof(Example));
}

Example contains(const char* pattern, const char* filePath)
{
	Example exDefault{ -1,"err" };
	std::ifstream ifs(filePath, std::ios::binary);
	if (ifs.is_open())
	{
		for (size_t i = 0; i < getFileSize(ifs) / sizeof(Example); i++)
		{
			Example ex = readExampleFromFile(ifs);
			if (strcmp(pattern, ex.buff) == 0)
			{
				return ex;
			}
		}
	}

	return exDefault;
}

int main()
{
	char filePath[20];
	std::cin >> filePath;

	std::ofstream ofs(filePath, std::ios::binary | std::ios::_Nocreate);
	if (!ofs.is_open())
	{
		return -1;
	}
	//fill file
	Example ex1{ 1, "aaa" };
	Example ex2{ 2, "bbb" };
	Example ex3{ 3, "ccc" };
	Example ex4{ 4, "aaa" };

	writeExample(ex1, ofs);
	writeExample(ex2, ofs);
	writeExample(ex3, ofs);
	writeExample(ex4, ofs);
	ofs.close();

	size_t countEx = examplesInFile(filePath);
	std::cout << "Examples count: " << countEx << std::endl;
	std::cout << "Enter pattern: ";
	char pattern[8];
	std::cin >> pattern;
	Example ex = contains(pattern, filePath);
	std::cout << "The example is: " << ex.data << ", " << ex.buff;
}
