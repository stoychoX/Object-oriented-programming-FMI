#include <iostream>
#include <fstream>

struct Pair {
	size_t X = 0;
	size_t Y = 0;
};

const size_t MAX_PAIRS_RELATION = 20;
struct Relation {
	size_t currPairsInRelation = 0;
	Pair pairs[MAX_PAIRS_RELATION];
};

Pair CreatePair(const int x, const int y)
{
	Pair pair{ x,y };
	return pair;
}

void InitPair(Pair& toInit, int x, int y)
{
	toInit.X = x;
	toInit.Y = y;
}

Pair ReadPairFromFile(std::ifstream& inFile)
{
	if (!inFile.is_open())
	{
		return CreatePair(0, 0);
	}
	Pair pair;
	int x, y;
	inFile >> x;
	inFile >> y;
	InitPair(pair, x, y);
	return pair;
}

void WritePairToFile(std::ofstream& outFile, const Pair& toWrite)
{
	if (!outFile.is_open())
	{
		return;
	}
	outFile << toWrite.X << " " << toWrite.Y << std::endl;
}

bool AddPair(Relation& arg, const Pair& toInsert)
{
	if (arg.currPairsInRelation < MAX_PAIRS_RELATION)
	{
		arg.pairs[arg.currPairsInRelation++] = toInsert;
		return true;
	}
	return false;
}

bool WriteRelation(const Relation& arg, const char* filePath)
{
	std::ofstream ofs(filePath);
	if (!ofs.is_open())
	{
		return false;
	}
	for (size_t i = 0; i < arg.currPairsInRelation; i++)
	{
		WritePairToFile(ofs, arg.pairs[i]);
	}
	ofs.close();
	return true;
}

bool ReadRelation(Relation& arg, const char* filePath)
{
	std::ifstream ifs(filePath);
	if (!ifs.is_open())
	{
		return false;
	}
	while (!ifs.eof())
	{
		Pair pair = ReadPairFromFile(ifs);
		if (!AddPair(arg, pair))
		{
			return false;
		}
	}
	
	ifs.close();
	return true;
}

void PrintRelation(const Relation& rel)
{
	for (size_t i = 0; i < rel.currPairsInRelation; i++)
	{
		Pair pair = rel.pairs[i];
		std::cout << "(" << pair.X << " : " << pair.Y << ")"<<std::endl;
	}
}

int main()
{
	Relation rel;
	if (ReadRelation(rel, "RelationA.txt"))
	{
		PrintRelation(rel);
		return 0;
	}
	std::cout << "Error";
	return -1;
	
}
