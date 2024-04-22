#pragma once
#include "../../Seminar07/String/String.h"

class Student
{
private:
	String name;
	size_t age;
public:
	Student(const String& name, size_t age);

	const String& getName() const;
};