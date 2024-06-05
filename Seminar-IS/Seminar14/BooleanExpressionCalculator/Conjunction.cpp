#include "Conjunction.h"

Conjunction::Conjunction(Expression* l, Expression* r) :
    BinaryExpression(l, r) {}

bool Conjunction::evaluate(const BooleanInterpretation& interpretation) const
{
    return left->evaluate(interpretation) && right->evaluate(interpretation);
}

Expression* Conjunction::clone() const
{
    return new Conjunction(left->clone(), right->clone());
}
