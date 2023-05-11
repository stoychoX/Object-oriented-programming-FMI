#include "RadioButton.h"
#include <iostream>

RadioButton::RadioButton(float _x, float _y, const char* _text, bool _isChecked)
{
	setX(_x);
	setY(_y);
	setText(_text);
	setButton(_isChecked);
}
void RadioButton::showDialog()
{
	std::cout << "Enter name for radiobutton: ";
	char buff[1024];
	std::cin.getline(buff, 1024);
	setText(buff);
	std::cout << "Is radiobutton on: ";
	int _isChecked;
	std::cin >> _isChecked;
	if (_isChecked != 1 && _isChecked != 0)
		_isChecked = 0;
	setButton(_isChecked);
	std::cout << "Enter value for x: ";
	float _x;
	std::cin >> _x;
	setX(_x);
	std::cout << "Enter value for y: ";
	float _y;
	std::cin >> _y;
	setY(_y);
}
void RadioButton::flip()
{
	isChecked = !isChecked;
}
bool RadioButton::isOn() const
{
	return isChecked;
}
void RadioButton::setText(const char* _text)
{
	if (strlen(text) > 16)
		throw std::invalid_argument("string too long!");

	strcpy(text, _text);
}
void RadioButton::setButton(bool _isChecked)
{
	isChecked = _isChecked;
}