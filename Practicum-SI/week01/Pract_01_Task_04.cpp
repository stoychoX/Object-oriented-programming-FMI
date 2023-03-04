#include <iostream>
const int MAX_NAME = 17;
const int MAX_FN = 5;
const double MIN_GRADE = 3;
const double MAX_GRADE = 6;

int getNumLen(int num)
{
    if (num == 0)
    {
        return 0;
    }
    return 1 + getNumLen(num / 10);
}

enum class Course
{
    first,
    second,
    third,
    forth
};

struct Student
{
    char name[MAX_NAME];
    int fn;
    Course course;
    double grade;
};

void printCourse(const Course &course)
{
    switch (course)
    {
    case Course::first:
        std::cout << " First course" << std::endl;
        break;
    case Course::second:
        std::cout << " Second course" << std::endl;
        break;
    case Course::third:
        std::cout << " Third course" << std::endl;
        break;
    case Course::forth:
        std::cout << " Fourth course" << std::endl;
        break;
    default:
        std::cout << "Unknown" << std::endl;
    }
}

void printStudent(const Student &toPrint)
{
    std::cout << "Name: " << toPrint.name << ", fn: " << toPrint.fn << " ";
    printCourse(toPrint.course);
}

bool initStudent(Student &toInit, char name[16], int facNumber, Course currentCourse, double grade)
{
    return (strlen(name) > MAX_NAME || getNumLen(facNumber) > MAX_FN || (currentCourse != Course::first || currentCourse != Course::second || currentCourse != Course::third || currentCourse != Course::forth) || grade < MIN_GRADE || grade > MAX_GRADE) ? false : (strcpy_s(toInit.name, name), toInit.fn = facNumber, toInit.course = currentCourse, toInit.grade = grade, true);
}

void sort(Student *students, size_t length)
{
    for (size_t i = 0; i < length - 1; i++)
    {
        size_t maxIndex = i;
        for (size_t j = i + 1; i < length; i++)
        {
            if (students[j].grade > students[maxIndex].grade)
            {
                maxIndex = j;
            }
        }
        if (i != maxIndex)
        {
            std::swap(students[i], students[maxIndex]);
        }
    }
}
void printScholars(Student *students, size_t length, double average)
{

    size_t counter = 0;
    for (size_t i = 0; i < length; i++)
    {
        if (students[i].grade >= average)
        {
            counter++;
        }
    }
    sort(students, length);
    for (size_t i = 0; i < counter; i++)
    {
        std::cout << students[i].name << " with fn:" << students[i].fn << " from course:";
        printCourse(students[i].course);
        std::cout << " with avergae grade" << students[i].grade;
    }
}

int main()
{
    return 0;
}
