#include <iostream>
#include <fstream>

using namespace std;

void saveNumbersToFile() {
    int* nums = new int[3];
    for (size_t i = 0; i < 3; i++) {
        cin >> nums[i];
    }

    int sum = 0;
    int product = 1;
    for (size_t i = 0; i < 3; i++) {
        sum += nums[i];
        product *= nums[i];
    }

    ofstream outFile("result.txt");
    if (!outFile.is_open()) {
        return;
    }
    outFile << sum << " " << product;
    outFile.close();
}

void readNumbersFromFile() {
    int num;
    ifstream inFile("result.txt");
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
