#include "utils.h"

unsigned getFileSize(std::ifstream& inFile)
{
    unsigned currentPos = inFile.tellg();
    inFile.seekg(0, std::ios::end);
    unsigned size = (unsigned)(inFile.tellg());
    inFile.seekg(currentPos, std::ios::beg);

    return size;
}
