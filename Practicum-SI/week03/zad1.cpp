#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

const int BUFFSIZE = 8;

struct Example {
    int data;
    char buff[BUFFSIZE];
};

void initArray(Example* const arr,const int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "struct " << (i + 1) << std::endl;
        std::cin >> arr[i].data;
        std::cin >> arr[i].buff;
    }
}

void initFilename(char* const filename) {
    std::cout << "filename" << std::endl;
    std::cin >> filename;
}

void writeStruct(const Example& e, std::ofstream& os) {
    os << e.data << '\n';
    os << e.buff << '\n';
}

bool writeStructsToFile(const Example* const arr, const int n,const char* const filename) {
    std::ofstream os(filename, std::ios::out | std::ios::app);
    if (!os.is_open()) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        writeStruct(arr[i], os);
    }

    os.close();
}

size_t elementCount(std::ifstream& is,const char element) {
    size_t count = 0;
    char cur = 0;
    while (true) {
        is.get(cur);
        if (is.eof()) {
            break;
        }
        if (cur == element) {
            count++;
        }
    }
    return count;
}

size_t examplesInFile(const char* filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return 0;
    }
    return (elementCount(file, '\n') / 2);
}

Example structPattern(const char* filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        Example e{ -1,"err"};
        return e;
    }

    char line[50];
    bool isBuff = false;
    int curData = -1;
    while (true) {
        int curPointer = file.tellg();
        file.getline(line, 50);
        if (file.eof() || strcmp(line, "") == 0) {
            break;
        }
        if (!isBuff) {
            file.seekg(curPointer);
            file >> curData;
            file.ignore();
            isBuff = true;
            continue;
        }

        if (strcmp(line, "pattern") == 0) {
            Example result;
            result.data = curData;
            strcpy(result.buff, line);
            return result;
        }

        isBuff = false;
    }

    Example result{ -1, "err" };
    return result;
}

int main(){
    int n;
    std::cin >> n;

    Example* arr = new Example[n];
    initArray(arr, n);

    char filename[50];
    initFilename(filename);

    writeStructsToFile(arr, n, filename);

    std::cout << "structure count in file:" << std::endl;
    std::cout << examplesInFile("testtest.txt") << std::endl;

    std::cout << "example struct:" << std::endl;
    Example e = structPattern("testtest.txt");
    std::cout << e.data << " ; " << e.buff;

    delete[] arr;
}