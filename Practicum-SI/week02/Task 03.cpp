#include <iostream>
#include <fstream>

struct pair
{
    unsigned x;
    unsigned y;
};

pair createPair(int x, int y)
{
    pair myPair;
    myPair.x = x;
    myPair.y = y;
    return myPair;
}

void initPair(pair& toInit, int x, int y)
{
    toInit.x = x;
    toInit.y = y;
}

pair readPairFromFile(std::ifstream& inFile)
{
    pair myPair;
    myPair.x = inFile.get();
    inFile.ignore();
    myPair.y = inFile.get();
}

void writePairToFile(std::ofstream& outFile, const pair& toWrite)
{
    outFile << toWrite.x<<std::endl<<toWrite.y;
}

struct relation
{
    pair myPairs[25];
    int pairCount;
};

bool addPair(relation& arg, pair& toInsert)
{
    if (arg.pairCount < 25)
    {
        arg.myPairs[arg.pairCount] = toInsert;
    }
}

bool writeRelation(const relation& arg, const char* filePath)
{
    std::ofstream myFileOut("filePath");

    if (!myFileOut.is_open())
    {
        return -1;
    }

    for (int i = 0; i < arg.pairCount; i++)
    {
        myFileOut << arg.myPairs[i].x << std::endl << arg.myPairs[i].y;
    }

    myFileOut.close();
}

bool readRelation(relation& arg, const char* filepath)
{
    std::ifstream myFileIn("filePath");

    if (!myFileIn.is_open())
    {
        return -1;
    }

    for (int i = 0; i < arg.pairCount; i++)
    {
        myFileIn >> arg.myPairs[i].x;
        myFileIn.ignore();
        myFileIn >> arg.myPairs[i].y;
    }

    myFileIn.close();
}


int main()
{
    
}