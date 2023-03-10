#include <iostream>
#include <fstream>
const int MAX_LEN_BUFF = 8;
struct Example {
    int data;
    char buff[MAX_LEN_BUFF];
};
size_t getFileSize(std::ifstream& file)
{
    size_t currentPos = file.tellg();
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(currentPos);
    return fileSize;
}
size_t examplesInFile(const char* filePath) {
    std::ifstream ifs(filePath);
    if (!ifs.is_open()) {
        return -1;
    }
    size_t fileSize = getFileSize(ifs);
    size_t count = fileSize / sizeof(Example);
    ifs.close();
    return count;
}
Example isInFilePattern(const char* filePath, const char * pattern) {
    std::ifstream ifs(filePath, std::ios::binary);
    if (!ifs.is_open() || pattern == nullptr) {
        return {-1, "err"};
    }
    int fileSize = getFileSize(ifs);
    int countStructs = fileSize / sizeof(Example);
    char * fileBuff = new char[fileSize];
    Example * examples = new Example[countStructs];
    for (int i = 0; i < countStructs; i++)
        ifs.read((char*)&examples[i], sizeof(Example));
    for (int i = 0; i < countStructs; i++) {
        if (std::strcmp(examples[i].buff, pattern) == 0) {
            delete[] fileBuff;
            ifs.close();
            Example returnEx = examples[i];
            delete[] examples;
            return returnEx;
        }
    }
    delete[] fileBuff;
    delete[] examples;
    ifs.close();
    return { -1, "err" };
}
void printExample(const Example& ex) {
    std::cout << "(" << ex.data << ", " << ex.buff << ")" << std::endl;
}
int main() {
    Example  ex = isInFilePattern("file.txt", "bgn");
    printExample(ex);
}