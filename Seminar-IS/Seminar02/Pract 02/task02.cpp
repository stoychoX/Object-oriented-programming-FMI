#include <iostream>
#include <fstream>

using namespace std;

void readSourceCode() {
    ifstream inFile("result.txt");
    if (!inFile.is_open()) {
        return;
    }

    size_t small_letters = 0;
    size_t big_letters = 0;
    size_t digits = 0;
    size_t other = 0;
    char symbol = inFile.get();

    while (!inFile.eof()) {
        if (symbol >= 'a' && symbol <= 'z') {
            small_letters++;
        }
        else if (symbol >= 'A' && symbol <= 'Z') {
            big_letters++;
        }
        else if (symbol >= '0' && symbol <= '9') {
            digits++;
        }
        else {
            other++;
        }
        symbol = inFile.get();
    }

    cout << "Small letters: " << small_letters << endl;
    cout << "Big letters:   " << big_letters << endl;
    cout << "Digits:        " << digits << endl;
    cout << "Other:         " << other << endl;
    cout << "Total:         " << small_letters + big_letters + digits + other << endl;
    
    inFile.close();
}

int main()
{
    readSourceCode();
}
