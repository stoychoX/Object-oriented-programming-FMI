#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable : 4996)

struct User
{
    char name[25]{};
};

struct Message
{
    User from;
    char* text = nullptr;
};

User createUser(const char* name)
{
    User toReturn;
    strcpy(toReturn.name, name);
    return toReturn;
}

Message createMessage(const User& from, const char* text)
{
    Message toReturn;
    toReturn.text = new char[strlen(text) + 1] {};
    strcpy(toReturn.text, text);

    toReturn.from = from;
    return toReturn;
}

void serializeMessage(const Message& m, std::ofstream& outFile)
{
    outFile.write((const char*)(&m.from), sizeof(m.from));
    size_t textLen = strlen(m.text);
    outFile.write((const char*)&textLen, sizeof(textLen));
    outFile.write(m.text, textLen);
}

Message readNextMessage(std::ifstream& inFile)
{
    Message toReturn;
    inFile.read((char*)&toReturn.from, sizeof(toReturn.from));
    size_t textLen = 0;
    inFile.read((char*)&textLen, sizeof(textLen));

    toReturn.text = new char[textLen + 1] {};
    inFile.read(toReturn.text, textLen);

    return toReturn;
}

void freeMessage(Message& m)
{
    delete[] m.text;
}

void createExample()
{
    std::ofstream outFile("chat.dat", std::ios::binary);

    Message msg[3] = {
        createMessage(createUser("Stoycho"), "Zdravei"),
        createMessage(createUser("Niki"), "Pari?"),
        createMessage(createUser("Stoycho"), "Ne...")
    };

    for (size_t i = 0; i < 3; i++)
    {
        serializeMessage(msg[i], outFile);
        freeMessage(msg[i]);
    }
}

void printMessage(const Message& m)
{
    std::cout << m.from.name << ": " << m.text << std::endl;
}

void printChat(const char* filePath)
{
    std::ifstream inFile(filePath, std::ios::binary);

    if (!inFile.is_open())
        return;

    while (true)
    {
        Message msg = readNextMessage(inFile);

        if (inFile.eof())
            break;
        printMessage(msg);
    }
}

int main()
{
    createExample();
    printChat("chat.dat");
}