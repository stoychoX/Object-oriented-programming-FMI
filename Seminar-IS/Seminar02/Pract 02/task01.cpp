#include <iostream>
#include <fstream>

using namespace std;

const char FILE_NAME[] = "result.txt";

void saveNumbersToFile() {
    int nums[3];
    for (size_t i = 0; i < 3; i++) {
        cin >> nums[i];
    }

    int sum = 0;
    int product = 1;
    for (size_t i = 0; i < 3; i++) {
        sum += nums[i];
        product *= nums[i];
    }

    ofstream outFile(FILE_NAME);
    if (!outFile.is_open()) {
        return;
    }
    outFile << sum << " " << product;
    outFile.close();
}

void readNumbersFromFile() {
    int num;
    ifstream inFile(FILE_NAME);
    if (!inFile.is_open()) {
        return;
    }
    while (!inFile.eof()) {
        inFile >> num;
        cout << num << endl;
    }
    inFile.close();
}

int main()
{
    saveNumbersToFile();
    readNumbersFromFile();
}
