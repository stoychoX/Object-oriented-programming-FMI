#pragma once
#include <iostream>

class String
{
private:
	char* data;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const String& other);

	size_t calculateCapacity(size_t size) const;

	void resize(size_t newCap);
public:
	String();
	String(const char* str);
	String(const String& other);
	
	String& operator=(const String& other);

	const char* c_str() const;
	char* getData();

	char operator[](size_t index) const;
	char& operator[](size_t index);

	size_t length() const;

	String& operator+=(const String& other);
	String& operator+=(char ch);

	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
	friend String operator+(const String& lhs, const String& rhs);

	friend std::ostream& operator<<(std::ostream& os, const String& str);
	friend std::istream& operator>>(std::istream& os, String& str);

	int find_if(bool (*pred)(char)) const;

	~String();
};


