#pragma once
#include "ComponentBase.h"

class Label : public ComponentBase
{
	char text[17] = { '\0' };
public:
	Label() = default;
	Label(float _x, float _y, const char* _text);
	void showDialog() override;
	void setText(const char* _text);
};