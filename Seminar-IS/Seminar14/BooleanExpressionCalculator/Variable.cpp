#include "Variable.h"

Variable::Variable(char symbol) :
    symbol(symbol) {}

char Variable::getSymbol() const
{
    return symbol;
}

bool Variable::evaluate(const BooleanInterpretation& interpretation) const
{
    return interpretation.getValue(symbol);
}

Expression* Variable::clone() const
{
    return new Variable(*this);
}

void Variable::fetchVariables(bool* variables) const
{
    variables[symbol - 'a'] = true;
}
