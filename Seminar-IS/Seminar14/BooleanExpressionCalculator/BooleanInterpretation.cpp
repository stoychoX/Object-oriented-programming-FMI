#include "BooleanInterpretation.h"

bool BooleanInterpretation::isValidVariable(char variable)
{
    return variable >= 'a' && variable <= 'z';
}

void BooleanInterpretation::setValue(char variable, bool value)
{
    if (isValidVariable(variable))
        values[variable - 'a'] = value;
}

bool BooleanInterpretation::getValue(char variable) const
{
    return isValidVariable(variable) && values[variable - 'a'];
}


BooleanInterpretation BooleanInterpretation::fromNumber(const bool* variablesIncluded, size_t number)
{
    BooleanInterpretation booleanInterpretation;
    
    for (size_t variable = 0; variable < VariableData::ALPHABET_SIZE; variable++)
	{
		if (variablesIncluded[variable])
		{
			bool value = (number % 2 == 1);
			number /= 2;
			booleanInterpretation.setValue(variable + 'a', value);
		}

        if(number == 0) return booleanInterpretation;
	}

    return booleanInterpretation;
}

