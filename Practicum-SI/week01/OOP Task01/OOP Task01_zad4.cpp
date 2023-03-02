#include <iostream>

const int STUDENT_COUNT = 5;

enum class Course
{
    Si,
    Is,
    I,
    Cs,
    unknown
};

void PrintCourse(const Course& c)
{
    switch (c)
    {
    case Course::Si:
        std::cout << "Software engineering";
        break;
    case Course::Is:
        std::cout << "Information systems";
        break;
    case Course::I:
        std::cout << "Informatics";
        break;
    case Course::Cs:
        std::cout << "Computer sience";
        break;
    default:
        std::cout << "Unknown";
        break;
    }
}

struct Student
{
    char name[16];
    int fnum = 0;
    Course course = Course::unknown;
    double grade = 2;
};

struct Univrsity
{
    Student students[STUDENT_COUNT];
};

void PrintStudent(const Student& toPrint)
{
    std::cout << toPrint.name << "  " << toPrint.fnum << std::endl;
    PrintCourse(toPrint.course);
    std::cout << " - " << toPrint.grade << std::endl;
    std::cout << std::endl;
}

bool InitStudent(Student& toInit)
{
    if (toInit.fnum > 99999 || toInit.fnum < 10000 || toInit.grade > 6 || toInit.grade < 2)
        return false;
    return true;
}

void SwapStudentsInArray(Student* students, int i)
{
    Student temp;
    temp = students[i - 1];
    students[i - 1] = students[i];
    students[i] = temp;
}

void IfBiggerGradeSwap(Student* students, int i)
{
    if (students[i].grade > students[i - 1].grade)
    {
        SwapStudentsInArray(students, i);
    }
}

void BubbleSort(Student* students, int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            IfBiggerGradeSwap(students, j);
        }
    }
}

bool IsAvarageGrade(Student* students, int i,int average)
{
    if (students[i].grade >= average)
        return 1;
    return 0;
}

void CheckPrinting(Student* students, size_t length, double average, int i)
{
    if (IsAvarageGrade(students, i, average) && InitStudent(students[i]))
    {
        PrintStudent(students[i]);
    }
}

void PrintStudents(Student* students, size_t length, double average)
{
    for (int i = 0; i < length; i++)
    {
        CheckPrinting(students, length, average, i);
    }
}

void PrintScholars(Student* students, size_t length, double average)
{
    BubbleSort(students, length);
    PrintStudents(students, length, average);
}

int main()
{
    Student students[5];
    students[0] = { "Ivan Petrov", 22434, Course::Cs, 5.3 };
    students[1] = { "Peter Ivanov", 22987, Course::Si, 3.5 };
    students[2] = { "Alex Angelov", 22212, Course::I, 3.9 };
    students[3] = { "Kristian Kasov", 32112, Course::I, 4.3 };
    students[4] = { "Ivan Ivanov", 12345, Course::Is, 4.8 };

    PrintScholars(students, 5, 4);
}
