#pragma once
#include <cstddef> // size_t
class String
{
private:
	char* data;
	size_t size;

	void copyFrom(const String& other);
	void free();

	void setData(const char* c);
public:
	String();
	String(const char* data);
	String(const String& other);
	String& operator=(const String& other);

	size_t length() const;
	const char* c_str() const;
	String& concat(const String& other);
	bool empty() const;
	~String();
};