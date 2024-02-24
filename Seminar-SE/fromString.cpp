#include <iostream>

enum class ErrorCode
{
	OK,
	NullPtr,
	InvalidString,
	Overflow
};

struct ResultPair
{
	int64_t value;
	ErrorCode code;
};

bool isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

ResultPair fromString(const char* str)
{
	if (str == nullptr)
		return { 0, ErrorCode::NullPtr };

	int64_t toReturn = 0;
	bool isNegative = (*str == '-');

	if (isNegative)
		++str;

	while (*str)
	{
		if (!isDigit(*str))
			return { toReturn, ErrorCode::InvalidString };

		int64_t temp = toReturn;

		temp *= 10;
		temp += (*str - '0');

		if (toReturn > temp)
			return { toReturn, ErrorCode::Overflow };
		
		toReturn = temp;
		
		++str;
	}
	if (isNegative)
		toReturn *= -1;

	return { toReturn, ErrorCode::OK };
}

int main()
{
	ResultPair p = fromString("1237346723");
	
	switch (p.code)
	{
	case ErrorCode::OK:
		std::cout << p.value;
		break;
	case ErrorCode::NullPtr:
		std::cout << "nullptr";
		break;
	case ErrorCode::InvalidString:
		std::cout << "invalid string";
		break;
	case ErrorCode::Overflow:
		std::cout << "overflow";
		break;
	default:
		std::cout << "Unknown error";
		break;
	}
}