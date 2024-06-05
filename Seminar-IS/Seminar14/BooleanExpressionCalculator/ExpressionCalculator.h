#pragma once
#include "Expression.h"
#include "../../../utils/String/String.h" 				// Worst way to include!
#include "../../../utils/StringView/StringView.h" 		// Every compile has include directories in which we place .h files
#include "../../../utils/Optional/optional.hpp"			// We should add utils to the include directories and include by: #include<optional/optional.hpp>

namespace ParserUtils
{
	String removeSpaces(const String& str);
	int findClosingBracketIndex(const StringView& str);
	Expression* applyNegation(Expression* e, bool isNegation);

	Expression* create(
		const StringView& left,
		char operation,
		const StringView& right,
		bool negateLeft,
		String& errorMessage);
	
	bool isValidOperation(char operation);
	int findFirstOperationIndex(const StringView& str);
	String removeSpaces(const String& str);
	bool isValidVariable(char ch);

	Expression* parse(StringView str, String& errorMessage);
}

using OptionalBool = Optional<bool>;

class ExpressionCalculator
{
private:
	Expression* expr;
	bool initialized = false;
	String errors;

	void free();
	void copyFrom(const ExpressionCalculator&);
	void move(ExpressionCalculator&& other);

	OptionalBool checkAllVariations(bool value) const;
public:
	ExpressionCalculator(const String& str);

	ExpressionCalculator(const ExpressionCalculator&);
	ExpressionCalculator(ExpressionCalculator&&) noexcept;

	OptionalBool eval(const BooleanInterpretation& interpretation) const;
	OptionalBool isTautology() const;
	OptionalBool isContradiction() const;
	
	const String& getErrors() const;
	bool good() const;

	bool tryParse(const String& expr);

	ExpressionCalculator& operator=(const ExpressionCalculator&);
	ExpressionCalculator& operator=(ExpressionCalculator&&) noexcept;

	~ExpressionCalculator();
};

