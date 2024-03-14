
#include <iostream>
#include <fstream>
#pragma warning (disable : 4996)
struct word
{
	char data[25]{};
	size_t density = 0;
};

size_t getFileSize(std::ifstream& inFile)
{
	size_t currentLocation = inFile.tellg();
	inFile.seekg(0, std::ios::end);
	size_t fileSize = inFile.tellg();
	inFile.seekg(currentLocation, std::ios::beg);

	return fileSize;
}

bool isPrefix(const char* fst, const char* snd)
{
	while (*fst && *snd && *fst == *snd)
	{
		++fst;
		++snd;
	}
	return (*fst == '\0');
}

size_t getScore(const char* wordArg, const char* filePath)
{
	std::ifstream inFile(filePath, std::ios::binary);
	
	if (!inFile.is_open())
		return 0;

	size_t fileSize = getFileSize(inFile);
	size_t recordSize = sizeof(word);

	size_t recordsCount = fileSize / recordSize;

	word* myWords = new word[recordsCount];
	
	inFile.read((char*)myWords, fileSize);

	size_t toReturn = 0;

	for (size_t i = 0; i < recordsCount; i++)
	{
		if (isPrefix(wordArg, myWords[i].data))
		{
			toReturn += myWords[i].density;
		}
	}

	delete[] myWords;

	return toReturn;
}

word createWord(const char* w, size_t density)
{
	word toReturn;
	strcpy(toReturn.data, w);
	toReturn.density = density;
	return toReturn;
}

void createExample()
{
	std::ofstream outFile("example.dat", std::ios::binary);
	word words[3] = {
		createWord("house", 2),
		createWord("home", 3),
		createWord("yard", 7)
	};

	outFile.write((const char*)&words, 3 * sizeof(word));
}

int main()
{
	createExample();
	std::cout << getScore("ho", "example.dat");
}