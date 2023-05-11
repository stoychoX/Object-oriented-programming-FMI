#include "Label.h"
#include <iostream>

Label::Label(float _x, float _y, const char* _text)
{
	setX(_x);
	setY(_y);
	setText(_text);
}

void Label::showDialog()
{
	std::cout << "Enter text for ther label: ";
	char buff[1024];
	std::cin.getline(buff, 1024);
	setText(buff);
	std::cout << "Enter value for x: ";
	float _x;
	std::cin >> _x;
	setX(_x);
	std::cout << "Enter value for y: ";
	float _y;
	std::cin >> _y;
	setY(_y);
}

void Label::setText(const char* _text)
{
	if (strlen(text) > 16)
		throw std::invalid_argument("string too long!");

	strcpy(text, _text);
}