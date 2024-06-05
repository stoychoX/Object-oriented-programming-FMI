#pragma once
#include "Expression.h"
class UnaryExpression :
    public Expression
{
protected:
    Expression* expr;
public:
    UnaryExpression(Expression* expr);
    void fetchVariables(bool* variables) const override;
    ~UnaryExpression();
};

