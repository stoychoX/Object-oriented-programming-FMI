#include "Negation.h"

Negation::Negation(Expression* expr) :
    UnaryExpression(expr) {}

bool Negation::evaluate(const BooleanInterpretation& interpretation) const
{
    return !expr->evaluate(interpretation);
}

Expression* Negation::clone() const
{
    return new Negation(expr->clone());
}
