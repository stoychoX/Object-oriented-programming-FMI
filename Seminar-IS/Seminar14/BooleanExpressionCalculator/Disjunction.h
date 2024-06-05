#pragma once
#include "BinaryExpression.h"
class Disjunction :
    public BinaryExpression
{
public:
    Disjunction(Expression* l, Expression* r);

    // Inherited via BinaryExpression
    virtual bool evaluate(const BooleanInterpretation& interpretation) const override;
    virtual Expression* clone() const override;
};

