#include "Student.h"

Student::Student(
    const char* name, 
    unsigned age, 
    unsigned facNum) :
    Person(name, age),
    facNum(facNum) {}

unsigned Student::getFacNum() const
{
    return facNum;
}
