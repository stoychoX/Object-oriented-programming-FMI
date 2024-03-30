#include "String.h"
#include <cstring>
#pragma warning(disable:4996)

void String::copyFrom(const String& other)
{
	setData(other.data);
}

void String::free()
{
	delete[] data;
}

void String::setData(const char* c)
{
	if (c == nullptr)
	{
		data = nullptr;
		return;
	}
	size_t len = strlen(c);
	data = new char[len + 1] {};
	strcpy(data, c);

	size = len;
}

String::String() : data(nullptr), size(0) {}

String::String(const char* data)
{
	setData(data);
}

String::String(const String& other)
{
	copyFrom(other);
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

size_t String::length() const
{
	return size;
}

const char* String::c_str() const
{
	return data;
}

String& String::concat(const String& other)
{
	if (other.empty())
		return *this;

	if (empty())
	{
		*this = other;
		return *this;
	}

	size_t newLen = length() + other.length();
	char* newData = new char[newLen + 1];
	strcpy(newData, data);
	strcat(newData, other.data);

	free();
	data = newData;
	return *this;
}

bool String::empty() const
{
	return (size == 0);
}

String::~String()
{
	free();
}