#include <iostream>
#pragma warning (disable : 4996)
#include <fstream>

class MyString
{
	char* _data;
	size_t size;

	void copyFrom(const MyString& data);
	void free();
public:

	MyString();
	MyString(const char* data);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);

	size_t length() const;

	MyString& operator+=(const MyString& other);
	char& operator[](size_t index);
	char operator[](size_t index) const;

	void append(const char* str);
	void clear();
	int first_of(char c) const;
	int last_of(char c) const;
	int first_not_of(char c) const;
	int last_not_of(char c) const;

	friend bool operator==(const MyString& lhs, const MyString& rhs);
	friend bool operator!=(const MyString& lhs, const MyString& rhs);
	friend bool operator<(const MyString& lhs, const MyString& rhs);
	friend bool operator>(const MyString& lhs, const MyString& rhs);
	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
	friend std::istream& operator>>(std::istream& is, MyString& str);
	~MyString();
};
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
MyString operator+(const MyString& lhs, const MyString& rhs);
std::ostream& operator<<(std::ostream& os, const MyString& str);
std::istream& operator>>(std::istream& is, const MyString& str);