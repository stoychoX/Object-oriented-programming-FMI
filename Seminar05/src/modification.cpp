#include "modification.h"
#include <cstring>

#pragma warning(disable : 4996)

Modification createPercentModif(const char* name, double percent, ModificationType type)
{
	Modification modif;
	modif.name = new char[strlen(name) + 1] {};
	strcpy(modif.name, name);

	modif.percent = percent;
	modif.amount = ModificationConstants::INVALID_AMOUNT;
	modif.type = type;

	return modif;
}

Modification createAmountModif(const char* name, unsigned amount, ModificationType type)
{
	Modification modif;
	modif.name = new char[strlen(name) + 1] {};
	strcpy(modif.name, name);

	modif.percent = ModificationConstants::INVALID_PERCENT;
	modif.amount = amount;
	modif.type = type;

	return modif;
}

bool isAmountModif(const Modification& modif)
{
	return modif.amount != ModificationConstants::INVALID_AMOUNT;
}

bool isPercentModif(const Modification& modif)
{
	return modif.percent != ModificationConstants::INVALID_PERCENT;
}

void writeModif(std::ofstream& outFile, const Modification& modif)
{
	unsigned nameSize = strlen(modif.name);

	outFile.write((const char*)(&nameSize), sizeof(nameSize));
	outFile.write(modif.name, nameSize);

	outFile.write((const char*)(&modif.amount), sizeof(modif.amount));
	outFile.write((const char*)(&modif.percent), sizeof(modif.percent));
	outFile.write((const char*)(&modif.type), sizeof(modif.type));
}

void readModif(std::ifstream& inFile, Modification& modif)
{
	unsigned nameSize = 0;
	inFile.read((char*)(&nameSize), sizeof(nameSize));

	modif.name = new char[nameSize + 1] {};
	inFile.read(modif.name, nameSize);
	modif.name[nameSize] = '\0';

	inFile.read((char*)(&modif.amount), sizeof(modif.amount));
	inFile.read((char*)(&modif.percent), sizeof(modif.percent));
	inFile.read((char*)(&modif.type), sizeof(modif.type));
}

void readModifications(const char* fileName, Modification*& modifs, unsigned& size)
{
	std::ifstream inFile(fileName, std::ios::binary);

	if (!inFile.is_open())
	{
		return;
	}

	inFile.read((char*)(&size), sizeof(size));
	modifs = new Modification[size]{};

	for (size_t i = 0; i < size; i++)
	{
		readModif(inFile, modifs[i]);
	}
}

void writeModifications(const char* fileName, const Modification* modifs, unsigned size)
{
	std::ofstream outFile(fileName, std::ios::binary);

	if (!outFile.is_open())
	{
		return;
	}

	outFile.write((const char*)(&size), sizeof(size));

	for (size_t i = 0; i < size; i++)
	{
		writeModif(outFile, modifs[i]);
	}
}
