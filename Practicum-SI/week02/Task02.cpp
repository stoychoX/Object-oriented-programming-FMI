#include <iostream>
#include <fstream>

const size_t LENGTH = 2;

bool Contains(const char& ch, const char arr[], size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		if (ch == arr[i])
		{
			return true;
		}
	}
	return false;
}

size_t GetSpecialSymbolsCount(const char* fileName, const char notSpecialSymbols[LENGTH], size_t length)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		return 0;
	}
	size_t countSpecialSymbols = 0;
	size_t currIndex = ifs.tellg();
	while (true)
	{
		if (ifs.eof())
		{
			break;
		}
		char currSymbol = ifs.get();
		if (!Contains(currSymbol, notSpecialSymbols, LENGTH))
		{
			countSpecialSymbols++;
		}
	}
	ifs.seekg(currIndex);
	ifs.clear();
	ifs.close();
	return countSpecialSymbols - 1;
}

int main()
{
	char symbols[2]{ 'a', 'd' };
	std::cout << GetSpecialSymbolsCount("File.txt", symbols, 2);//14
}

