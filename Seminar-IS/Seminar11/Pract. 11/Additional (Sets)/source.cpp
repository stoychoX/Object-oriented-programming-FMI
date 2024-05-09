#pragma once
#include <fstream>
#include <iostream>
#include "CriteriaSet.h"
#include "IntervalSet.h"
#include "FiniteSet.h"
#include "Union.h"
#include "Intersection.h"

Set* readFiniteSet(std::ifstream& reader, int elementsCount)
{
	Vector setNumbers;

	for (size_t i = 0; i < elementsCount; i++)
	{
		int number;
		reader.read((char*)&number, sizeof(int));

		setNumbers.push_back(number);
	}

	return new FiniteSet(setNumbers);
}

Set* readIntervalSet(std::ifstream& reader, int elementsCount)
{
	if (elementsCount != 2)
	{
		return nullptr;
	}

	int leftBound, rightBound;
	reader.read((char*)&leftBound, sizeof(int));
	reader.read((char*)&rightBound, sizeof(int));

	return new IntervalSet(leftBound, rightBound);
}

Set* readCriteriaSet(std::ifstream& reader, int elementsCount)
{
	Vector setNumbers;

	for (size_t i = 0; i < elementsCount; i++)
	{
		int number;
		reader.read((char*)&number, sizeof(int));

		setNumbers.push_back(number);
	}

	Criteria criteria;

	return new CriteriaSet(setNumbers, criteria);
}

Set* readIntersection(std::ifstream& reader, int elementsCount)
{
	if (elementsCount != 4)
	{
		return nullptr;
	}

	int lhsLeftBound, lhsRightBound;
	int rhsLeftBound, rhsRightBound;

	reader.read((char*)&lhsLeftBound, sizeof(int));
	reader.read((char*)&lhsRightBound, sizeof(int));
	reader.read((char*)&rhsLeftBound, sizeof(int));
	reader.read((char*)&rhsRightBound, sizeof(int));

	Set* lhsInterval = new IntervalSet(lhsLeftBound, lhsRightBound);
	Set* rhsInterval = new IntervalSet(rhsLeftBound, rhsRightBound);

	return new Intersection(lhsInterval, rhsInterval);
}

Set* readUnion(std::ifstream& reader, int elementsCount)
{
	if (elementsCount != 4)
	{
		return nullptr;
	}

	int lhsLeftBound, lhsRightBound;
	int rhsLeftBound, rhsRightBound;

	reader.read((char*)&lhsLeftBound, sizeof(int));
	reader.read((char*)&lhsRightBound, sizeof(int));
	reader.read((char*)&rhsLeftBound, sizeof(int));
	reader.read((char*)&rhsRightBound, sizeof(int));

	Set* lhsInterval = new IntervalSet(lhsLeftBound, lhsRightBound);
	Set* rhsInterval = new IntervalSet(rhsLeftBound, rhsRightBound);

	return new Union(lhsInterval, rhsInterval);
}

Set* readSet(std::ifstream& reader, uint8_t setType, int elementsCount)
{
	if (setType == 0)
	{
		return readFiniteSet(reader, elementsCount);
	}
	else if (setType == 1)
	{
		return readIntervalSet(reader, elementsCount);
	}
	else if (setType == 2)
	{
		return readCriteriaSet(reader, elementsCount);
	}
	else if (setType == 3)
	{
		return readIntersection(reader, elementsCount);
	}
	else if (setType == 4)
	{
		return readUnion(reader, elementsCount);
	}

	return nullptr;
}

uint8_t getSetType(uint8_t setInfo)
{
	return (setInfo >> 5);
}

Set* readSetFromBinaryFile(const char* binaryFileName)
{
	std::ifstream binaryFileReader(binaryFileName, std::ios::binary);

	if (!binaryFileReader.good())
	{
		return nullptr;
	}

	int elementsCount;
	binaryFileReader.read((char*)&elementsCount, sizeof(int));

	uint8_t setInfo;
	binaryFileReader.read((char*)&setInfo, sizeof(uint8_t));

	uint8_t setType = getSetType(setInfo);

	Set* set = readSet(binaryFileReader, setType, elementsCount);

	binaryFileReader.close();

	return set;
}

int main()
{
	{
		std::ofstream writer("files.txt");
		writer << "first.dat";
		writer.close();
	}

	{
		std::ofstream bWritier("first.dat", std::ios::binary);

		int nums = 10;
		bWritier.write((const char*)&nums, sizeof(int));

		uint8_t setInfo = 64;
		bWritier.write((const char*)&setInfo, sizeof(uint8_t));

		for (size_t i = 1; i <= 10; i++)
		{
			bWritier.write((const char*)&i, sizeof(int));
		}

		bWritier.close();
	}

	{
		std::ifstream fileReader("files.txt");

		if (!fileReader.is_open())
		{
			return -1;
		}

		char binaryFileName[64];
		fileReader.getline(binaryFileName, 64);

		fileReader.close();

		Set* set = readSetFromBinaryFile(binaryFileName);

		if (!set)
		{
			std::cout << "Invalid set" << std::endl;
			return -1;
		}

		set->print(std::cout);

		std::cout << set->operator[](20);
	}
}
