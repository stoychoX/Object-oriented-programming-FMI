#include "Implication.h"

Implication::Implication(Expression* l, Expression* r) :BinaryExpression(l, r) {}

bool Implication::evaluate(const BooleanInterpretation& interpretation) const
{
    return !left->evaluate(interpretation) || right->evaluate(interpretation);
}

Expression* Implication::clone() const
{
    return new Implication(left->clone(), right->clone());
}
