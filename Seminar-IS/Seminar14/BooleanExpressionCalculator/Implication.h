#pragma once
#include "BinaryExpression.h"
class Implication :
    public BinaryExpression
{
public:
    Implication(Expression* l, Expression* r);

    // Inherited via BinaryExpression
    virtual bool evaluate(const BooleanInterpretation& interpretation) const override;
    virtual Expression* clone() const override;
};

