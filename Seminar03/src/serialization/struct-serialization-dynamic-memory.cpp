#include <iostream>
#include <fstream>
#include <cstring>

// This structure has heap allocated memory.
struct Student
{
    unsigned id;
    unsigned age;
    char* name = nullptr;
};

Student createStudent(const char* name, unsigned id, unsigned age)
{
    Student s;
    s.id = id;
    s.age = age;

    unsigned nameLen = strlen(name);
    s.name = new char[nameLen]{};
    strncpy(s.name, name, nameLen);

    return s;
}

void freeStudent(Student& s)
{
    delete[] s.name;
}

void writeStudent(const char* fileName, const Student& s)
{
    std::ofstream outFile(fileName, std::ios::binary);

    if(!outFile.is_open())
    {
        std::cout << "Cannot open file " << fileName << std::endl;
        return;
    }

    unsigned nameLen = strlen(s.name);
    // We can be smart here and write two variables with one write
    // but it may not be a good idea as we depend on the variable positions.
    outFile.write((const char*)(&s.id), sizeof(s.id));
    outFile.write((const char*)(&s.age), sizeof(s.age));

    outFile.write((const char*)(&nameLen), sizeof(nameLen));
    outFile.write(s.name, nameLen);
}

void readStudent(const char* fileName, Student& s)
{
    std::ifstream inFile(fileName, std::ios::binary);

    if(!inFile.is_open())
    {
        std::cout << "Cannot open file " << fileName << std::endl;
        return;
    }

    inFile.read((char*)(&s.id), sizeof(s.id));
    inFile.read((char*)(&s.age), sizeof(s.age));

    unsigned nameLen = 0;
    inFile.read((char*)(&nameLen), sizeof(nameLen));
    s.name = new char[nameLen]{};

    inFile.read(s.name, nameLen);
}

void printStudent(const Student& s)
{
    std::cout << s.name << " " << s.age << " " << s.id << std::endl;
}

int main()
{
    const char* filename = "student.dat";

    Student example = createStudent("Stoycho", 1, 23);

    std::cout << "Created student: ";
    printStudent(example);
    std::cout << "Writing student in file " << filename << std::endl;
    writeStudent(filename, example);

    std::cout << "Reading student from file " << filename << std::endl;

    Student exampleClone;
    readStudent(filename, exampleClone);

    std::cout << "The value of the new student is: ";
    printStudent(exampleClone);

    freeStudent(example);
    freeStudent(exampleClone);
}