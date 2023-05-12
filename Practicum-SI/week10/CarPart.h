#pragma once
#include <iostream>

class CarPart
{
	static unsigned carPartsCreated;
	unsigned id = 0;
	char* prodName = nullptr;
	char* desc = nullptr;
	void free();
	void moveFrom(CarPart&& other);
protected:
	void printInfo() const;
public:
	CarPart() = default;
	CarPart(const char* _prodName, const char* _desc);
	CarPart(CarPart&& other);
	CarPart& operator=(CarPart&& other);
	~CarPart();

	void setProdName(const char* _prodName);
	void setDesc(const char* _desc);

	const char* getProdName() const;
	const char* getDesc() const;
	unsigned getId() const;
};