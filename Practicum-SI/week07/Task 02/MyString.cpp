#include "MyString.h"

void MyString::copyFrom(const MyString& data)
{
	this->size = data.size;
	_data = new char[size + 1];
	strcpy(_data, data._data);
}

void MyString::free()
{
	delete[] _data;
	_data = nullptr;
	size = 0;
}

MyString::MyString()
{
	_data = new char[1];
	_data[0] = '\0';
	size = 0;
}

MyString::MyString(const char* data)
{
	if (data == nullptr)
	{
		size = 0;
		_data = new char[1];
		_data[0] = '\0';
	}
	else
	{
		size = strlen(data);
		_data = new char[size + 1];
		strcpy(_data, data);
	}
}


MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

size_t MyString::length() const
{
	return size;
}

MyString& MyString::operator+=(const MyString& other)
{
	size_t totalSize = size + other.size;
	char* dataCopy = new char[totalSize + 1];
	dataCopy[0] = '\0';
	strcat(dataCopy, _data);
	strcat(dataCopy, other._data);

	free();
	size = totalSize;
	_data = dataCopy;

	return *this;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return (strcmp(lhs._data, rhs._data) == 0);
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
	return (strcmp(lhs._data, rhs._data) < 0);
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
	return (!(lhs < rhs) && !(lhs == rhs));
}

char& MyString::operator[](size_t index)
{
	return _data[index];//lvalue
}

char MyString::operator[](size_t index) const
{
	return _data[index];//rvalue
}

void MyString::append(const char* str)
{
	if (str != nullptr)
	{
		size_t totalSize = size + strlen(str);
		char* concStr = new char[totalSize + 1];
		concStr[0] = '\0';

		strcat(concStr, _data);
		strcat(concStr, str);

		free();
		_data = concStr;
		size = totalSize;
	}
}

void MyString::clear()
{
	free();
	_data = new char[1];
	_data[0] = '\0';
}

namespace
{
	size_t changeIndex(bool toUp, size_t& index)
	{
		return toUp ? index++ : index--;
	}
	bool checkIndex(size_t indexCurr, size_t indexLast, bool isLessThan)
	{
		return isLessThan ? indexCurr < indexLast : indexCurr > indexLast;
	}
	int getIndexOf(char c, const char* data, unsigned startIndex, unsigned endIndex, bool (*predicate)(char a, char b))
	{
		bool increase = true;
		bool isLessThan = true;
		if (startIndex > endIndex)
		{
			increase = false;
			isLessThan = false;
			
		}
		for (size_t i = startIndex; checkIndex(i, endIndex, isLessThan); changeIndex(increase, i))
		{
			if (predicate(data[i], c))
			{
				return i;
			}
		}
		return -1;
	}
	bool areEqual(char a, char b)
	{
		return a == b;
	}
	bool areNotEqual(char a, char b)
	{
		return !areEqual(a,b);
	}
}

int MyString::first_of(char c) const
{
	return getIndexOf(c, _data, 0, size - 1, areEqual);
}

int MyString::last_of(char c) const
{
	return getIndexOf(c, _data, size - 1, 0, areEqual);
}

int MyString::first_not_of(char c) const
{
	return getIndexOf(c, _data,0, size - 1, areNotEqual);
}

int MyString::last_not_of(char c) const
{
	return getIndexOf(c, _data, size - 1, 0, areNotEqual);
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString str(lhs);
	str += rhs;
	return str;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	os << str._data << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	is >> str._data;
	return is;
}

MyString::~MyString()
{
	free();
}