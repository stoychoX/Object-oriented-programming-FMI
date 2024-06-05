#pragma once
#include "BooleanInterpretation.h"

class Expression
{
public:
	virtual bool evaluate(const BooleanInterpretation& interpretation) const = 0;
	virtual Expression* clone() const = 0;
	virtual void fetchVariables(bool* variables) const = 0;

	virtual ~Expression() = default;
};

