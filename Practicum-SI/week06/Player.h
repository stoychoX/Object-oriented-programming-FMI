#pragma once
#include "Guess.h" 
class Player
{
private:
	char* name = nullptr;
	char* password = nullptr;
	unsigned age = 0;
	double money = 0.0;

	void free();
	void copyFrom(const Player& other);
public:
	Player(const char* name, const char* pass, unsigned age, double money);
	Player(const Player& other);
	Player& operator=(const Player& other);
	~Player();

	const char* getName() const;
	const char* getPass() const;
	unsigned getAge() const;
	double getMoney() const;
	void setName(const char* name);
	void setPass(const char* pass);
	void setMoney(double money);

	Guess guess() const;
};