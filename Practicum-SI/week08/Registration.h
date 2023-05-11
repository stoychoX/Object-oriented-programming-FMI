#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <cstring>

class Registration
{
	char data[9];
	bool isValid(const char* str)const;
public:
	Registration(const char* str);
	Registration& operator=(const char* str);

	bool operator==(const Registration& other) const;
	const char* toString() const;
};