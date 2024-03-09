
#include <iostream>
#include <fstream>

size_t getFileSize(std::ifstream &inFile)
{
    size_t currentPos = inFile.tellg();
    inFile.seekg(0, std::ios::end);

    size_t size = inFile.tellg();

    inFile.seekg(currentPos, std::ios::beg);

    return size;
}

// Split even numbers in the left part of the array
// and odd numbers in the right part.

// We can always allocate two new arrays, one for the odd and one for the
// even numbers. Then just copy even numbers in the first array and odd numbers
// in odd array and dump them in separate files.

// This splits even and odd numbers and makes it possible
// to dump them in separate files without allocating two new arrays.
size_t split(int *numbers, size_t size)
{
    size_t begin = 0;
    size_t end = size - 1;

    while (true)
    {
        while (begin != end && numbers[begin] % 2 == 1)
        {
            std::swap(numbers[begin], numbers[end]);
            --end;
        }

        if (begin == end)
            break;
        begin++;
    }

    if (numbers[begin] % 2 == 0)
        ++begin;

    return begin;
}

void writeToFile(const int *numbers, size_t size, const char *filePath)
{
    std::ofstream outFile(filePath, std::ios::binary);

    if (!outFile.is_open())
        return;

    outFile.write((const char *)(numbers), size * sizeof(int));
}

void oddEvenSplit(const char *filePath, const char *oddFilePath, const char *evenFilePath)
{
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile.is_open())
        return;

    size_t size = getFileSize(inFile);
    size_t numbersSize = size / sizeof(int);

    int *numbers = new int[numbersSize]{};
    inFile.read((char *)numbers, numbersSize * sizeof(int));

    for (size_t i = 0; i < numbersSize; i++)
    {
        std::cout << numbers[i] << " ";
    }

    size_t evenCount = split(numbers, numbersSize);
    // even
    writeToFile(numbers, evenCount, evenFilePath);

    // odd
    writeToFile(numbers + evenCount, numbersSize - evenCount, oddFilePath);
}

void createDemo(const char *demo)
{
    constexpr size_t size = 4;
    int arr[size] = {1, 2, 3, 4};
    std::ofstream outFile(demo, std::ios::binary);

    outFile.write((const char *)arr, size * sizeof(int));
}

int main()
{
    createDemo("demo.dat");
    oddEvenSplit("demo.dat", "odd.dat", "even.dat");
}