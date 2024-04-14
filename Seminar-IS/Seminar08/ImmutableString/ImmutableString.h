#pragma once
#include <iostream>
#include "StringPool.h"

class ImmutableString
{
private:
	const char* data;
	unsigned size;

	static StringPool pool;

public:
	ImmutableString();
	ImmutableString(const char* text);
	ImmutableString(const ImmutableString& other);

	char operator[](size_t index) const;

	ImmutableString& operator=(const ImmutableString& other);

	const char* c_str() const;

	size_t length() const;
	bool empty() const;

	static void debug();

	~ImmutableString();
};

bool operator==(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs);
std::ostream& operator<<(std::ostream& os, const ImmutableString& str);