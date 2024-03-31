#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

constexpr size_t MAX_NAME_SIZE = 22;
struct Student
{
    // gender should be BEFORE fn so the struct would be 28 bytes.
    char name[MAX_NAME_SIZE + 1];
    bool isMale;
    unsigned fn;
};

bool isLower(char ch)
{
    return ch >= 'a' && ch <= 'z';
}

bool areAllLowerCase(const char *str)
{
    if (str == nullptr) {
        return false;
    }
    while (*str)
    {
        if (!isLower(*str))
            return false;
        str++;
    }
    return true;
}

bool isUpper(char ch)
{
    return ch >= 'A' && ch <= 'Z';
}

bool isNameValid(const char *name)
{
    if (name == nullptr) {
        return false;
    }
    size_t len = strlen(name);
    if (len == 0 || len > MAX_NAME_SIZE)
        return false;
    return isUpper(*name) && areAllLowerCase(name + 1);
}

void initStudent(Student &st, const char *name, size_t fn, bool isMale)
{
    if (!isNameValid(name))
        strcpy(st.name, "Unknown");
    else
        strcpy(st.name, name);

    st.isMale = isMale;
    st.fn = fn;
}

void saveToFile(const Student *students, size_t count, ofstream &file)
{
    file.write((const char *)students, count * sizeof(Student));
}

size_t getFileSize(ifstream &f)
{
    size_t currentPos = f.tellg();
    f.seekg(0, ios::end);
    size_t size = f.tellg();

    f.seekg(currentPos);
    return size;
}

void readFromFile(Student *&ptr, size_t &studentsCount, ifstream &f)
{
    size_t sizeOfFile = getFileSize(f);
    studentsCount = sizeOfFile / sizeof(Student);
    ptr = new Student[studentsCount];
    f.read((char *)ptr, sizeOfFile);
}

int main()
{
    {
        const size_t studentsCount = 4;
        Student *arr = new Student[studentsCount];
        initStudent(arr[0], "Ivan", 1, true);
        initStudent(arr[1], "Petur", 2, true);
        initStudent(arr[2], "Alex", 3, true);
        initStudent(arr[3], "Katerina", 4, false);

        ofstream file("students.dat", ios::binary);

        if (!file.is_open())
        {
            std::cout << "Error while opening the file!" << std::endl;
            delete[] arr; //!
            return -1;
        }

        saveToFile(arr, studentsCount, file);

        delete[] arr;
    }

    {
        Student *arr;
        size_t count;
        ifstream file("students.dat");

        if (!file.is_open())
        {
            std::cout << "Error while opening the file!" << std::endl;
            return -1;
        }

        readFromFile(arr, count, file);

        for (int i = 0; i < count; i++)
            std::cout << "Name: " << arr[i].name << ", fn: " << arr[i].fn << ", is male: " << arr[i].isMale << std::endl;

        delete[] arr;

        return 0;
    }

    return 0;
}