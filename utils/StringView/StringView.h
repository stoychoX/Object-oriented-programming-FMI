#pragma once
#include "../String/String.h"

class StringView
{
private:
	const char* begin;
	const char* end; // One element after the last element
public:
	StringView(const char* str);
	StringView(const char* begin, const char* end);
	StringView(const String& str);

	StringView substr(size_t pos, size_t off) const;
	StringView substr(size_t pos) const;
	void remove_prefix(size_t size);
	void remove_suffix(size_t size);

	size_t lenght() const;
	char operator[](size_t idx) const;
	char at(size_t idx) const;

    friend std::ostream& operator<<(std::ostream& os, const StringView& view);

	bool empty() const;
};
