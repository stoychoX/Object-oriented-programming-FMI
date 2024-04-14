#include "ImmutableString.h"
#pragma warning (disable:4996)
#include <cstring>
#include <cassert>

StringPool ImmutableString::pool;

ImmutableString::ImmutableString() : ImmutableString("") {}

ImmutableString::ImmutableString(const char* text)
{
	data = pool.getString(text);
	size = strlen(data);
}

ImmutableString::ImmutableString(const ImmutableString& other)
{
	data = pool.getString(other.c_str());
	size = other.size;
}

void ImmutableString::debug()
{
	ImmutableString::pool.debug();
}


char ImmutableString::operator[](size_t index) const
{
	if (index >= size)
		throw std::out_of_range("ImmutableString::operator[] out of range!");

	return data[index];
}

ImmutableString& ImmutableString::operator=(const ImmutableString& other)
{
	if (this != &other)
	{
		pool.removeString(data);
		data = pool.getString(other.c_str());
		size = other.size;
	}

	return *this;
}

const char* ImmutableString::c_str() const
{
	return data;
}

size_t ImmutableString::length() const
{
	return size;
}

bool ImmutableString::empty() const
{
	return (size == 0);
}

ImmutableString::~ImmutableString()
{
	pool.removeString(c_str());
}

bool operator==(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const ImmutableString& str)
{
	return os << str.c_str();
}