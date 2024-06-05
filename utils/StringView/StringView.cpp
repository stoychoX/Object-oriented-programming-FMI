#include "StringView.h"
#include <cstring>

StringView::StringView(const char* str) :
	StringView(str, str + strlen(str)) {}

StringView::StringView(const char* begin, const char* end) :
	begin(begin),
	end(end) {}

StringView::StringView(const String& str) :
	StringView(str.c_str(), str.c_str() + str.length()) {}

StringView StringView::substr(size_t pos, size_t off) const
{
	if (lenght() < pos + off)
		throw std::runtime_error("Invalid string view substr operation");

	return StringView(begin + pos, begin + pos + off);
}

StringView StringView::substr(size_t pos) const
{
	return substr(pos, lenght() - pos);
}

void StringView::remove_prefix(size_t size)
{
	if (size >= lenght())
		size = lenght();

	begin += size;
}

void StringView::remove_suffix(size_t size)
{
	if (size >= lenght())
		size = lenght();
	
	end -= size;
}

size_t StringView::lenght() const
{
	return (end - begin);
}

char StringView::operator[](size_t idx) const
{
	return *(begin + idx);
}

char StringView::at(size_t idx) const
{
	if (idx >= lenght())
		throw std::invalid_argument("Invalid index at StringView::at");

	return *(begin + idx);
}

bool StringView::empty() const
{
	return (begin == end);
}

std::ostream& operator<<(std::ostream& os, const StringView& view)
{
    if(os.good())
    {
        os.write(view.begin, view.lenght());
    }
    
    return os;
}
