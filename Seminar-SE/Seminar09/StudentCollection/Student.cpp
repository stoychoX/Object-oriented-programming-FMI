#include "Student.h"

Student::Student(const String& name, size_t age) :
	name(name), age(age) {}

const String& Student::getName() const
{
	return name;
}