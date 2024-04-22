#pragma once
#include <iostream>

class String
{
private:
	char* data;
	unsigned size;

	void free();
	void copyFrom(const String& other);
	void move(String&& other);
public:
	String();
	String(const char* text);
	String(const String& other);
	String(String&& other);

	char operator[](size_t index) const;
	char& operator[](size_t index);

	String& operator+=(const String& other);
	String& operator=(const String& other);
	String& operator=(String&& other);

	const char* c_str() const;

	size_t length() const;
	bool empty() const;

	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
	friend std::ostream& operator<<(std::ostream& os, const String& str);

	~String();
};

String operator+(const String& lhs, const String& rhs);