#include "Person.h"
#include <cstring>
#include <utility>
#pragma warning(disable : 4996)
void Person::free()
{
	delete[] name;
}

void Person::copyFrom(const Person& other)
{
	setName(other.name);
	age = other.age;
}

void Person::move(Person&& other)
{
	name = other.name;
	other.name = nullptr;
	age = other.age;
}

void Person::setName(const char* oldName)
{
	delete[] name;

	size_t len = strlen(oldName);
	name = new char[len + 1] {};
	strcpy(name, oldName);
}

Person::Person() : Person(nullptr, 0) {}

Person::Person(const char* name, unsigned age) :
	name(nullptr),
	age(age)
{
	setName(name);
}

Person::Person(const Person& other)
{
	copyFrom(other);
}

Person::Person(Person&& other)
{
	move(std::move(other));
}

Person& Person::operator=(const Person& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Person& Person::operator=(Person&& other)
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}
	return *this;
}

const char* Person::getName() const
{
	return name;
}

unsigned Person::getAge() const
{
	return age;
}

Person::~Person()
{
	free();
}
