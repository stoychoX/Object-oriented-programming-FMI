#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(Expression* l, Expression* r) :
	left(l),
	right(r)
{
}

void BinaryExpression::fetchVariables(bool* variables) const
{
	left->fetchVariables(variables);
	right->fetchVariables(variables);
}

BinaryExpression::~BinaryExpression()
{
	delete left;
	delete right;
}
