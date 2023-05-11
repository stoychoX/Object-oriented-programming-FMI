#include "ComponentBase.h"

class RadioButton : public ComponentBase
{
	char text[17] = { '\0' };
	bool isChecked = false;
public:
	RadioButton() = default;
	RadioButton(float _x, float _y, const char* _text, bool _isChecked);
	void showDialog() override;
	void flip();
	bool isOn() const;
	void setText(const char* _text);
	void setButton(bool _isChecked);
};