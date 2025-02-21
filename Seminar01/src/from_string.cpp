#include <iostream>

enum class StatusCode
{
	OK,
	NullptrPassed,
	InvalidString,
	Overflow
};

struct Result
{
	StatusCode code;
	int64_t result;
};

Result create_result(StatusCode code, int64_t result)
{
	return { code , result };
}

bool is_digit(char ch)
{
	return ch >= '0' && ch <= '9';
}

Result from_string(const char* number)
{
	if (number == nullptr)
	{
		return create_result(StatusCode::NullptrPassed, -1);
	}

	int64_t to_return = 0;

	bool is_negative = (*number == '-');

	if(is_negative)
	{
		number++;
	}

	while (*number != '\0')
	{
		char current_digit = *number;

		if (!is_digit(current_digit))
		{
			return create_result(StatusCode::InvalidString, -1);
		}

		int64_t candidate = to_return * 10;

		if (candidate < to_return)
		{
			return create_result(StatusCode::Overflow, -1);
		}
		to_return = candidate;

		to_return += current_digit - '0';
		++number;
	}

	if (is_negative)
		to_return *= -1;

	return create_result(StatusCode::OK, to_return);
}

int main()
{
	Result result = from_string("-123");

	if (result.code == StatusCode::OK)
	{
		std::cout << result.result;
	}
	else if (result.code == StatusCode::Overflow)
	{
		std::cout << "Overflow";
	}
	else if(result.code == StatusCode::InvalidString)
	{
		std::cout << "Invalid string passed";
	}
	else if (result.code == StatusCode::NullptrPassed)
	{
		std::cout << "nullptr passed";
	}
}