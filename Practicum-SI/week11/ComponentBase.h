#pragma once

class ComponentBase
{
	float x;
	float y;
public:
	ComponentBase() = default;
	ComponentBase(float _x, float _y);
	virtual void showDialog() = 0;
	void move(float dx, float dy);
	virtual ~ComponentBase() = default;
protected:
	void setX(float _x);
	void setY(float _y);
};