#pragma once
#include <iostream>
const int MAX_COUNT_PAIRS = 25;

struct Pair {
	int num1;
	int num2;
};

void CreatePair(const Pair& pair)
{
	std::cout << pair.num1 << pair.num2;
}

void InitPair(Pair& pair)
{
	std::cin >> pair.num1 >> pair.num2;
}

Pair ReadPairFromFile(std::ifstream& file)
{
	Pair* newPair = new Pair;
	file >> newPair->num1 >> newPair->num2;
	
	return *newPair;
}

void WritePairToFile(std::ofstream& file, const Pair& pair)
{
	file << pair.num1 << ' ' << pair.num2 << "\n";
}

struct Relation {
	Pair pairs[MAX_COUNT_PAIRS];
	int len = 0;
};

bool AddPair(Relation& relation, const Pair& pairToAdd)
{
	int lenRel = relation.len;
	if (lenRel == 25) return false;

	relation.pairs[lenRel] = pairToAdd;
	relation.len++;
}

bool WriteRelation(const Relation& relation, const char* filePath)
{
	std::ofstream file(filePath);
	if (!file.is_open()) { return false; }

	for (int i = 0; i < relation.len; i++)
	{
		WritePairToFile(file, relation.pairs[i]);
	}

	file.close();
	return true;
}

bool ReadRelation(Relation& relation, const char* filePath) 
{
	std::ifstream file(filePath);
	if (!file.is_open()) { return false; }

	while (relation.len < 25)
	{
		relation.pairs[relation.len] = ReadPairFromFile(file);
		relation.len++;

		if (file.eof()) 
		{
			relation.len--;
			break;
		}
	}
	
	file.close();
	return true;
}

void ExecuteTask3()
{
	//std::ofstream myFile("pairs.txt");
	//if (!myFile.is_open()) { return; }

	//Pair pair = { 100, 10 };

	Relation relation;
	ReadRelation(relation, "pairs.txt");

	relation;
	std::cout << (relation.len);
	
	//for (int i = 0; i < relation.len; i++)
	//{
	//	delete relation.pairs[i];
	//}
	//delete[] relation;

	//myFile.close();
}