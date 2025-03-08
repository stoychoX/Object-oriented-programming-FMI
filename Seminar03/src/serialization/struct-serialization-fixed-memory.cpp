#include <iostream>
#include <fstream>
#include <cstring>

constexpr const unsigned STUDENT_NAME_LEN = 26;

// This structure has no heap allocated memory.
struct Student
{
    unsigned id;
    unsigned age;
    char name[STUDENT_NAME_LEN]{};
};

Student createStudent(const char* name, unsigned id, unsigned age)
{
    Student s;
    s.id = id;
    s.age = age;

    strncpy(s.name, name, STUDENT_NAME_LEN);

    return s;
}

void writeStudent(const char* fileName, const Student& s)
{
    std::ofstream outFile(fileName, std::ios::binary);

    if(!outFile.is_open())
    {
        std::cout << "Cannot open file " << fileName << std::endl;
        return;
    }

    // We need only one write.
    outFile.write((const char*)(&s), sizeof(s));
}

void readStudent(const char* fileName, Student& s)
{
    std::ifstream inFile(fileName, std::ios::binary);

    if(!inFile.is_open())
    {
        std::cout << "Cannot open file " << fileName << std::endl;
        return;
    }

    inFile.read((char*)(&s), sizeof(s));
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
}