#include <iostream>
#include <fstream>

size_t fileSize(std::ifstream& inFile)
{
	size_t currentPos = inFile.tellg();
	inFile.seekg(0, std::ios::end);
	size_t fileSize = inFile.tellg();

	inFile.seekg(currentPos, std::ios::beg);

	return fileSize;
}

void getEvenAndOddCount(const int* arr, size_t size, size_t& evenCount, size_t& oddCount)
{
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] % 2 == 0)
		{
			++evenCount;
		}
		else
		{
			++oddCount;
		}
	}
}

void fillEven(int* evenArray, size_t evenArraySize, int* arr, size_t numbersSize)
{
	size_t at = 0;
	for (size_t i = 0; i < numbersSize; i++)
	{
		if (arr[i] % 2 == 0)
		{
			if (evenArraySize <= at) return;

			evenArray[at++] = arr[i];
		}
	}
}

void fillOdd(int* oddArray, size_t oddArraySize, int* arr, size_t numbersSize)
{
	size_t at = 0;
	for (size_t i = 0; i < numbersSize; i++)
	{
		if (arr[i] % 2 == 1)
		{
			if (oddArraySize <= at) return;

			oddArray[at++] = arr[i];
		}
	}
}

void dumpInFile(const char* filePath, const int* arr, size_t size)
{
	std::ofstream outFile(filePath, std::ios::binary);

	if (!outFile.is_open())
		return;
	outFile.write((const char*)arr, size);
}

void split(const char* filePath, const char* oddPath, const char* evenPath)
{
	std::ifstream inFile(filePath, std::ios::binary);

	if (!inFile.is_open())
		return;

	size_t size = fileSize(inFile);
	size_t numbersCount = size / sizeof(int);

	int* numbers = new int[numbersCount] {};

	inFile.read((char*)(numbers), numbersCount * sizeof(int));
	size_t evenCount = 0;
	size_t oddCount = 0;
	getEvenAndOddCount(numbers, numbersCount, evenCount, oddCount);

	int* even = new int[evenCount] {};
	int* odd  = new int[oddCount] {};

	fillEven(even, evenCount, numbers, numbersCount);
	fillOdd(odd, oddCount, numbers, numbersCount);

	dumpInFile(oddPath, odd, oddCount * sizeof(int));
	dumpInFile(evenPath, even, evenCount * sizeof(int));

	delete[] numbers;
	delete[] even;
	delete[] odd;
}

void createExample()
{
    std::ofstream outFile("demo.dat", std::ios::binary);
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    outFile.write((const char*)arr, 10 * sizeof(int));
}

int main()
{
    createExample();
	split("demo.dat", "odd.dat", "even.dat");
}