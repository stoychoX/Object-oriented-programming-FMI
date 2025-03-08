#include <iostream>
#include <fstream>

void fpos_examples()
{
    const char *file_name = "positioning_example.txt";

    std::ofstream outFile(file_name);

    if (!outFile.is_open())
    {
        std::cout << "File positioning example failed" << std::endl;
        return;
    }

    for (size_t i = 0; i < 26; i++)
    {
        // Write all the letters from 'a' to 'z' to a file.
        outFile << (char)(i + 'a');
    }

    outFile.close();

    std::ifstream inFile(file_name);

    if (!inFile.is_open())
    {
        std::cout << "File positioning example failed" << std::endl;
        return;
    }

    while (true)
    {
        unsigned pos = 0;
        std::cout << "Enter a position in " << file_name << ": ";
        std::cin >> pos;

        if (!std::cin.good() || pos > 25)
        {
            // Some streams error handling!
            std::cout << "Please enter a number between 0 and 25!" << std::endl;

            // Flip back good flag.
            std::cin.clear();
            
            // Ignore all symbols up to a new line.
            // Ignore does nothing if the stream is not in `good` state!
            std::cin.ignore(255, '\n');

            continue;
        }

        inFile.seekg(pos, std::ios::beg);

        std::cout << "The " << pos << " letter is " << (char)inFile.peek() << std::endl;
    }
}

int main()
{
    fpos_examples();
}