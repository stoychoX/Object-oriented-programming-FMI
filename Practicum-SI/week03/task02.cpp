#include <iostream>
#include <fstream>

struct Example {
    int data;
    char buff[8];
};

size_t examplesInFile(const char* filePath) {
    std::ifstream input(filePath, std::ios::in | std::ios::binary);
    if(!input.is_open()) {
        return -1;
    }

    size_t count;

    input.seekg(0, std::ios::end);
    count = input.tellg() / sizeof(Example);

    input.close();
    return count;
}

int main() {
    std::cout << examplesInFile("data.dat") << std::endl;
    
    return 0;
}