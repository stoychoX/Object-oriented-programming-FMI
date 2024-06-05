#pragma once
#include <cstddef>

namespace VariableData
{
	constexpr unsigned ALPHABET_SIZE = 26;
}

class BooleanInterpretation
{
private:
	bool values[VariableData::ALPHABET_SIZE] = { false };
public:
	void setValue(char variable, bool value);
	bool getValue(char variable) const;
	static bool isValidVariable(char variable);

	static BooleanInterpretation fromNumber(const bool* variablesIncluded, size_t number);
};

