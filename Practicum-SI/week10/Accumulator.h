#pragma once
#include "CarPart.h"

class Accumulator : public CarPart
{
	unsigned cap = 0;
	char* batteryId = nullptr;
	void free();
	void moveFrom(Accumulator&& other);
public:
	Accumulator() = default;
	Accumulator(const char* _prodName, const char* _desc, unsigned _cap, const char* _battId);
	Accumulator(Accumulator&& other);
	Accumulator& operator=(Accumulator&& other);
	~Accumulator();

	void setBatteryId(const char* _battId);

	unsigned getCap() const;
	const char* getBattId() const;
};