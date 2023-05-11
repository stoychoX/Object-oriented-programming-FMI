#include "ComponentBase.h"

ComponentBase::ComponentBase(float _x, float _y)
{
	x = _x;
	y = _y;
}
void ComponentBase::move(float dx, float dy)
{
	x += dx;
	y += dy;
}
void ComponentBase::setX(float _x)
{
	x = _x;
}
void ComponentBase::setY(float _y)
{
	y = _y;
}