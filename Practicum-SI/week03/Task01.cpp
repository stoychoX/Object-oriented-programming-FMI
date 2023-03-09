#include <iostream>
#include <fstream>
const int MAX_LEN_LINE = 1024;
const int MAX_LEN_FILE = 30;
struct Example {
    int data;
    char buff[8];
};
bool saveToFileBinary(std::ofstream& ofs, const Example* examples, size_t size) {
    if (!ofs.is_open() || size <= 0 || examples == nullptr) {
        return false;
    }
    ofs.write((const char*)examples, sizeof(Example) * size);
    return true;
}
int main() {
    int n;
    std::cin >> n;
    Example * arr = new Example[n];
    char str[MAX_LEN_LINE];
    int data;
    for (int i = 0; i < n; i++) {
        std::cin >> data;
        std::cin.ignore();//1 space is ignored
        std::cin.getline(str, MAX_LEN_LINE);
        arr[i].data = data;
        strcpy_s(arr[i].buff, str);
    }
    char nameOfFile[MAX_LEN_FILE];
    std::cin.getline(nameOfFile, MAX_LEN_FILE);
    std::ofstream ofs(nameOfFile, std::ios::binary | std::ios::app);
    if (!ofs.is_open()) {
        std::cout << "Error to open file" << std::endl;
        return -1;
    }
    saveToFileBinary(ofs, arr, n);
    delete[] arr;
    ofs.close();
}