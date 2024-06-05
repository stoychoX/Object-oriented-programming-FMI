#pragma once
#include "Expression.h"
class BinaryExpression :
    public Expression
{
protected:
    Expression* left;
    Expression* right;
public:
    BinaryExpression(Expression* l, Expression* r);

    void fetchVariables(bool* variables) const override;

    ~BinaryExpression();
};

