#include "Teacher.h"

#include <cstring>
#include <utility>
#pragma warning(disable : 4996)

char* Teacher::copyString(const char* oldString) const
{
	size_t len = strlen(oldString);
	char* toReturn = new char[len + 1] {};
	strcpy(toReturn, oldString);

	return toReturn;
}

void Teacher::copyFrom(const Teacher& other)
{
	subjectsLen = other.subjectsLen;

	subjects = new char* [subjectsLen] {};

	for (size_t i = 0; i < subjectsLen; i++)
		subjects[i] = copyString(other.subjects[i]);
}

void Teacher::free()
{
	for (size_t i = 0; i < subjectsLen; i++)
		delete[] subjects[i];
	delete[] subjects;
}

void Teacher::move(Teacher&& other)
{
	subjects = other.subjects;
	subjectsLen = other.subjectsLen;

	other.subjects = nullptr;
	other.subjectsLen = 0;
}

Teacher::Teacher() : Teacher(nullptr, 0, nullptr, 0) {}

Teacher::Teacher(
	const char* name, 
	unsigned age, 
	const char* const* argSubjects, 
	unsigned subjectsLen) :
	Person(name, age),
	subjects(nullptr),
	subjectsLen(subjectsLen)
{
	subjects = new char* [subjectsLen] {};
	for (size_t i = 0; i < subjectsLen; i++)
		subjects[i] = copyString(argSubjects[i]);
}

Teacher::Teacher(const Teacher& other) :
	Person(other)
{
	copyFrom(other);
}

Teacher::Teacher(Teacher&& other) :
	Person(std::move(other))
{
	move(std::move(other));
}

Teacher& Teacher::operator=(const Teacher& other)
{
	if (this != &other)
	{
		Person::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
}

Teacher& Teacher::operator=(Teacher&& other)
{
	if (this != &other)
	{
		Person::operator=(std::move(other));
		free();
		copyFrom(other);
	}
	return *this;
}

const char* Teacher::operator[](size_t idx) const
{
	return subjects[idx];
}

Teacher::~Teacher()
{
	free();
}
