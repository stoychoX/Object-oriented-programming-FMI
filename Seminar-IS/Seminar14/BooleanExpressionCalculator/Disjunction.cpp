#include "Disjunction.h"

Disjunction::Disjunction(Expression* l, Expression* r) :
    BinaryExpression(l, r) {}

bool Disjunction::evaluate(const BooleanInterpretation& interpretation) const
{
    return left->evaluate(interpretation) || right->evaluate(interpretation);
}

Expression* Disjunction::clone() const
{
    return new Disjunction(left->clone(), right->clone());
}
