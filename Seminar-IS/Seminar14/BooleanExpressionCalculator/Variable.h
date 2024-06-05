#pragma once
#include "Expression.h"
class Variable :
    public Expression
{
private:
    char symbol;
public:
    Variable(char symbol);

    char getSymbol() const;

    // Inherited via Expression
    virtual bool evaluate(const BooleanInterpretation& interpretation) const override;
    virtual Expression* clone() const override;
    void fetchVariables(bool* variables) const override;
};

