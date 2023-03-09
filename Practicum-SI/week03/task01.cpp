#include <iostream>
#include <fstream>

struct Example {
    int data;
    char buff[8];
};

bool appendToFile(std::ofstream &output, const Example* arr, const size_t len) {
    if(!output.is_open()) {
        return false;
    }

    size_t curPos = output.tellp();
    output.seekp(0, std::ios::end);
    
    output.write((const char*)arr, sizeof(arr[0]) * len);

    output.seekp(curPos, std::ios::beg);
    return true;
}

int main() {
    int n;
    std::cout << "Enter count of items:" << std::endl;
    std::cin >> n;

    Example* examples = new Example[n];
    for(int i = 0; i < n; i++) {
        std::cout << "Enter element #" << (i + 1) << ":" << std::endl;
        examples[i] = Example{};
        std::cin >> examples[i].data;
        std::cin.ignore(1, ' ');
        std::cin.getline(examples[i].buff, 8);
    }
    
    std::cout << "Enter path" << std::endl;
    char path[1024];
    std::cin.getline(path, 1024);

    std::ofstream output(path, std::ios::out | std::ios::binary | std::ios::app);
    appendToFile(output, examples, n);

    output.close();
    delete[] examples;
    return 0;
}