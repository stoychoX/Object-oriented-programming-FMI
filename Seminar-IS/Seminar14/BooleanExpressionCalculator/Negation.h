#pragma once
#include "UnaryExpression.h"
class Negation :
    public UnaryExpression
{
public:
    Negation(Expression* expr);

    // Inherited via UnaryExpression
    virtual bool evaluate(const BooleanInterpretation& interpretation) const override;
    virtual Expression* clone() const override;
};

