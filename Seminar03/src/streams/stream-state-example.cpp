#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>

void show_state(const std::istream &s, const char *message)
{
    std::cout << message << std::endl
              << "Good: " << s.good() << std::endl
              << "Bad: " << s.bad() << std::endl
              << "Fail: " << s.fail() << std::endl
              << "EOF: " << s.eof() << std::endl;
}

void show_state(const std::ostream &s, const char* message)
{
    std::cout << message << std::endl
              << "Good: " << s.good() << std::endl
              << "Bad: " << s.bad() << std::endl
              << "Fail: " << s.fail() << std::endl
              << "EOF: " << s.eof() << std::endl;
}

void state_examples()
{
    const char* file_name = "state-example1.txt";
    std::ofstream outFile(file_name);

    // This could fail (as example) if we dont 
    // have permissions to write in the file.
    if (!outFile.is_open())
    {
        show_state(outFile, "Output file stream state when file cannot be open.");
        std::cout << "Good state example failed" << std::endl;
        return;
    }

    show_state(outFile, "Output file stream state after opening a file.");

    outFile << 10;

    show_state(outFile, "Output file stream state after writing a number in it.");

    outFile << "Hello world!";

    show_state(outFile, "Output file stream state after writing \"Hello world\" in it");

    outFile.close();

    std::ifstream inFile(file_name);

    if(!inFile.is_open())
    {
        std::cout << "Good state example failed.";
        return;
    }

    int x = 0;
    inFile >> x;

    show_state(inFile, "Input file stream state after successfully reading a number from file.");
    assert(x == 10);
    
    char buffer[64]{};

    inFile.getline(buffer, 64);

    show_state(inFile, "Input file stream state after reading \"Hello world\" from the file.");
    assert(strcmp(buffer, "Hello world!") == 0);

    char c = inFile.get();

    show_state(inFile, "State after trying to read after the end of the stream.");

    inFile.close();

    show_state(inFile, "State when the stream is closed.");

    // Re-open the stream.
    inFile.open(file_name);

    show_state(inFile, "State when we re-open it.");

    // Ignore the integer
    inFile.ignore(2, ' ');

    // Try to write to an integer when no integer is present
    inFile >> x;

    show_state(inFile, "State when we try to read integer when no integer is present");

    inFile.clear();

    show_state(inFile, "State when `clear` is invoked.");

    inFile.close();
}

int main()
{
    state_examples();
}