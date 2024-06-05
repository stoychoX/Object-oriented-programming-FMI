#pragma once
#include "BinaryExpression.h"
class Conjunction :
    public BinaryExpression
{
public:
    Conjunction(Expression* l, Expression* r);

    // Inherited via BinaryExpression
    virtual bool evaluate(const BooleanInterpretation& interpretation) const override;
    virtual Expression* clone() const override;
};

