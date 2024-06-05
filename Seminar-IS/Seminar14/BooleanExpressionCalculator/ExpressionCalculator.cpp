#include "ExpressionCalculator.h"
#include "Variable.h"
#include "Negation.h"
#include "Conjunction.h"
#include "Disjunction.h"
#include "Implication.h"
#include <stdexcept>

namespace ParserUtils
{
	String removeSpaces(const String& str)
	{
		String toReturn;
		for (size_t i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ')
				toReturn += str[i];
		}
		return toReturn;
	}

	bool isValidVariable(char ch)
	{
		return ch >= 'a' && ch <= 'z';
	}

	int findClosingBracketIndex(const StringView& str)
	{
		size_t depth = 0;
		size_t lastBracketIndex = 0;
		for (size_t i = 0; i < str.lenght(); i++)
		{
			if (str[i] == '(')
			{
				++depth;
			}
			else if (str[i] == ')')
			{
				--depth;
				if (depth == 0)
				{
					return i;
				}
			}
		}

		return -1;
	}

	Expression* applyNegation(Expression* e, bool isNegation)
	{
		return isNegation ? new Negation(e) : e;
	}

	Expression* create(
		const StringView& left, 
		char operation, 
		const StringView& right, 
		bool negateLeft,
		String& errorMessage)
	{
		if (operation == '&')
		{
			return new Conjunction(
				applyNegation(parse(left, errorMessage), negateLeft),
				parse(right, errorMessage));
		}
		else if (operation == '|')
		{
			return new Disjunction(
				applyNegation(parse(left, errorMessage), negateLeft),
				parse(right, errorMessage));
		}
		else if (operation == '>')
		{
			return new Implication(
				applyNegation(parse(left, errorMessage), negateLeft),
				parse(right, errorMessage)
			);
		}

		errorMessage += "Unknown operation \n";
		return nullptr;
	}

	bool isValidOperation(char operation)
	{
		return operation == '&' || operation == '|' || operation == '>';
	}

	int findFirstOperationIndex(const StringView& str)
	{
		int firstOperationIndex = -1;
		for (size_t i = 0; i < str.lenght(); i++)
		{
			if (isValidOperation(str[i]))
			{
				return i;
			}
		}
		return -1;
	}

	Expression* parse(StringView str, String& errorMessage)
	{
		// Negation
		bool negation = false;
		if (str[0] == '!')
		{
			negation = true;
			str = str.substr(1);
		}

		// variable:
		if (str.lenght() == 1)
		{
			if (!BooleanInterpretation::isValidVariable(str[0]))
			{
				errorMessage += "Invalid variable" + str[0] + '\n';
				return nullptr;
			}

			return applyNegation(new Variable(str[0]), negation);
		}

		if (str[0] == '(')
		{
			int lastBracketIndex = ParserUtils::findClosingBracketIndex(str);

			if (lastBracketIndex == -1)
			{
				errorMessage += "Invalid brackets in passed string \n";
				return nullptr;
			}

			StringView left = str.substr(1, lastBracketIndex - 1);

			// we have (expr) case
			if (lastBracketIndex == str.lenght() - 1)
			{
				return applyNegation(
					parse(str.substr(1, str.lenght() - 2), errorMessage),
					negation);
			}

			char op = str[lastBracketIndex + 1];

			StringView right = str.substr(lastBracketIndex + 2);

			return create(left, op, right, negation, errorMessage);
		}

		int firstOperationIndex = findFirstOperationIndex(str);
		if (firstOperationIndex == -1)
		{
			errorMessage += "No operation can be found\n";
			return nullptr;
		}

		StringView left = str.substr(0, firstOperationIndex);
		char op = str[firstOperationIndex];
		StringView right = str.substr(firstOperationIndex + 1);

		return create(left, op, right, negation, errorMessage);
	}
}

void ExpressionCalculator::free()
{
	delete expr;
	expr = nullptr;
}

void ExpressionCalculator::copyFrom(const ExpressionCalculator& other)
{
	expr = other.good() ? other.expr->clone() : nullptr;
	errors = other.errors;
	initialized = other.initialized;
}

void ExpressionCalculator::move(ExpressionCalculator&& other)
{
	expr = other.expr;
	other.expr = nullptr;

	errors = other.errors;
	initialized = other.initialized;
}

OptionalBool ExpressionCalculator::checkAllVariations(bool value) const
{
	if (!good())
		return {};

	bool* variablesIncluded = new bool[VariableData::ALPHABET_SIZE] { false };

	expr->fetchVariables(variablesIncluded);
	unsigned variablesCount = 0;
	for (size_t i = 0; i < VariableData::ALPHABET_SIZE; i++)
		if (variablesIncluded[i] == true)
			++variablesCount;

	size_t limit = (1ull << variablesCount);

	// Iterate all boolean vectors representing all boolean interpretations.
	for (size_t i = 0; i < limit; i++)
	{
		BooleanInterpretation booleanInterpretation = BooleanInterpretation::fromNumber(variablesIncluded, i);
		
		if (eval(booleanInterpretation).value() != value)
		{
			delete[] variablesIncluded;
			return false;
		}
	}

	delete[] variablesIncluded;
	return true;
}

ExpressionCalculator::ExpressionCalculator(const String& str) :
	expr(nullptr)
{
	using namespace ParserUtils;

	expr = parse(removeSpaces(str), errors);
	if (errors.length())
	{
		free();
	}
	else
	{
		initialized = true;
	}
}

ExpressionCalculator::ExpressionCalculator(const ExpressionCalculator& other)
{
	copyFrom(other);
}

ExpressionCalculator::ExpressionCalculator(ExpressionCalculator&& other) noexcept
{
	move(std::move(other));
}

OptionalBool ExpressionCalculator::eval(const BooleanInterpretation& interpretation) const
{
	if(good())
		return expr->evaluate(interpretation);
	return {};
}

OptionalBool ExpressionCalculator::isTautology() const
{
	return checkAllVariations(true);
}

OptionalBool ExpressionCalculator::isContradiction() const
{
	return checkAllVariations(false);
}

const String& ExpressionCalculator::getErrors() const
{
	return errors;
}

bool ExpressionCalculator::good() const
{
	return initialized;
}

bool ExpressionCalculator::tryParse(const String& str)
{
	using namespace ParserUtils;
	free();
	errors = "";

	expr = parse(removeSpaces(str), errors);

	if (errors.length())
	{
		free();
		initialized = false;
	}
	else
	{
		initialized = true;
	}

	return initialized;
}

ExpressionCalculator& ExpressionCalculator::operator=(const ExpressionCalculator& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

ExpressionCalculator& ExpressionCalculator::operator=(ExpressionCalculator&& other) noexcept
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}
	return *this;
}

ExpressionCalculator::~ExpressionCalculator()
{
	free();
}
