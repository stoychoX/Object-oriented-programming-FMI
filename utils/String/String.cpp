#include "String.h"
#include <cstring>
#include <cassert>
#pragma warning(disable:4996)

void String::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;
}

// could be a downsize too.
void String::resize(size_t newCap)
{
	char* newData = new char[newCap]{};
	size_t dataSize = std::min(newCap, size);
	strncpy(newData, data, dataSize);

	size = dataSize;
	capacity = newCap;
	delete[] data;
	data = newData;
}

char* String::getData()
{
	return data;
}

void String::copyFrom(const String& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new char[capacity];
	strcpy(data, other.data);
}

size_t String::length() const
{
	return size;
}

String& String::operator+=(char ch)
{
	if(size < capacity - 1)
	{
		data[size++] = ch;
		data[size] = '\0';
		return *this;
	}

	resize(calculateCapacity(capacity));
	assert(size < capacity);
	*this += ch;
	return *this;
}

size_t String::calculateCapacity(size_t argSize) const
{
	if (argSize < 16)
		return 16;

	return argSize + argSize / 2;
}

String::String() : String("") {}

String::String(const char* str)
{
	size = strlen(str);
	capacity = calculateCapacity(size);
	data = new char[capacity];
	strcpy(data, str);
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

const char* String::c_str() const
{
	return data;
}

char String::operator[](size_t index) const
{
	assert(index < size);
	return data[index];
}

char& String::operator[](size_t index)
{
	assert(index < size);
	return data[index];
}

String& String::operator+=(const String& other)
{
	if (size + other.size < capacity)
	{
		strncat(data, other.data, other.length());
		size += other.size;
		return *this;
	}
	
	resize(calculateCapacity(size + other.size));
	strncat(data, other.data, other.length());
	return *this;
}

int String::find_if(bool(*pred)(char)) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (pred(data[i]))
		{
			return i;
		}
	}
	return -1;
}

String::~String()
{
	free();
}

bool operator==(const String& lhs, const String& rhs)
{
	return (strcmp(lhs.data, rhs.data) == 0);
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}

String operator+(const String& lhs, const String& rhs)
{
	String str(lhs);
	str += rhs;
	return str;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os << str.data;
}

std::istream& operator>>(std::istream& os, String& str)
{
	char buff[1024]{};
	os >> buff;
	str = buff;
	return os;
}
