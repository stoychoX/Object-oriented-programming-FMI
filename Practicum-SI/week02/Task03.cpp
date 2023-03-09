#include <iostream>
#include <fstream>

namespace pairs
{
    struct pair
    {
        int x;
        int y;
    };

    pair createPair(int x, int y)
    {
        pair Pair = {x, y};
        return Pair;
    }

    void initPair(pair &toInit, int x, int y)
    {
        toInit.x = x;
        toInit.y = y;
    }

    pair readPairFromFile(std::ifstream &inFile)
    {
        if (!inFile.is_open())
        {
            std::cout << "Error!";
        }
        // казваме че искаме да четем от файла два инта
        int x, y;
        // прочитаме фикс и игрек
        inFile >> x >> y;
        // създаваме двойката и й даваме стойностите, които сме прочели

        pair pair;
        initPair(pair, x, y);

        inFile.close();
        return pair;
    }

    void writePairToFile(std::ofstream &outFile, const pair &toWrite)
    {
        if (!outFile.is_open())
        {
            std::cout << "Error!";
            return;
        }
        outFile << toWrite.x << " " << toWrite.y;
        outFile.close();
    }
}

namespace relations
{
    using namespace pairs;
    const int MAX_COUNT_PAIRS = 25;

    struct relation
    {
        pair pairs[MAX_COUNT_PAIRS];
        size_t currentCount = 0;
    };

    bool addPair(relation &arg, pair &toInsert)
    {
        if (arg.currentCount >= MAX_COUNT_PAIRS)
        {
            return false;
        }
        arg.pairs[arg.currentCount] = toInsert;
        arg.currentCount++;
        return true;
    }

    bool writeRelation(const relation &arg, const char *filePath)
    {
        std::ofstream outputStream(filePath);
        if (!outputStream.is_open())
        {
            std::cout << "Error!";
            return false;
        }

        outputStream << arg.currentCount << std::endl;

        for (size_t i = 0; i < arg.currentCount; i++)
        {
            writePairToFile(outputStream, arg.pairs[i]);
        }
        outputStream.close();
        return true;
    }

    bool readRelation(relation &arg, const char *filepath)
    {
        std::ifstream inputStream(filepath);
        if (!inputStream.is_open())
        {
            std::cout << "Error!";
            return false;
        }

        inputStream >> arg.currentCount;

        for (size_t i = 0; i < arg.currentCount; i++)
        {
            arg.pairs[i] = readPairFromFile(inputStream);
        }
        inputStream.close();
        return true;
    }
}

int main()
{
   

    return 0;
}
