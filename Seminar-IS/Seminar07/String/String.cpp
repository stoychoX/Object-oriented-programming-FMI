#include "String.h"
#pragma warning (disable:4996)
#include <cstring>
#include <cassert>

void String::free()
{
	delete[] data;
	size = 0;
}

void String::copyFrom(const String& other)
{
	data = new char[other.size + 1];
	strcpy(data, other.data);
	size = other.length();
}

String::String() : String("") {}

String::String(const char* text)
{
	size = strlen(text);
	data = new char[size + 1];
	strcpy(data, text);
}

String::String(const String& other)
{
	copyFrom(other);
}

char String::operator[](size_t index) const
{
	assert(index <= size);
	return data[index];
}

char& String::operator[](size_t index)
{
	assert(index <= size);
	return data[index];
}

String& String::operator+=(const String& other)
{
	size = size + other.size;
	char* newData = new char[size + 1];
	strcpy(newData, data);
	strcat(newData, other.data);

	delete[] data;
	data = newData;

	return *this;
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

const char* String::c_str() const
{
	return data;
}

size_t String::length() const
{
	return size;
}

bool String::empty() const
{
	return (size == 0);
}

String::~String()
{
	free();
}

bool operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os << str.c_str();
}

String operator+(const String& lhs, const String& rhs)
{
	String str(lhs);
	str += rhs;
	return str;
}