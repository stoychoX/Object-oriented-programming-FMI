#include "Registration.h"

static bool isCapitalLatinLetter(char ch)
{
	return ch >= 'A' && ch <= 'Z';
}
static bool isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

bool Registration::isValid(const char* str)const
{
	size_t strLen = strlen(str);
	if (str!=nullptr && (strLen==7 || strLen == 8))
	{
		if (isCapitalLatinLetter(str[0]))
		{
			size_t firstDigitIndex = 1;
			if (isCapitalLatinLetter(str[1]))
			{
				firstDigitIndex = 2;
			}
			size_t i = firstDigitIndex;
			for (; i < firstDigitIndex+4; i++)
			{
				if (!isDigit(str[i]))
				{
					return false;
				}
			}
			if (isCapitalLatinLetter(str[i]) && isCapitalLatinLetter(str[i+1]))
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

Registration::Registration(const char* str)
{
	if (str == nullptr)
	{
		throw std::invalid_argument("String does not exist!");
	}
	if (!isValid(str))
	{
		strcpy(data, "X XXXX X");
		data[8] = '\0';
	}
	else
	{
		strcpy(data, str);
		data[strlen(str)] = '\0';
	}
}
Registration& Registration::operator=(const char* str)
{
	if (str == nullptr)
	{
		throw std::invalid_argument("String does not exist!");
	}
	if (!isValid(str))
	{
		throw std::invalid_argument("Registration number is not valid!");
	}
	strcpy(data, str);
	data[strlen(str)] = '\0';
}

bool Registration::operator==(const Registration& other) const
{
	return strcmp(data, other.data) == 0;
}

const char* Registration::toString() const
{
	return data;
}