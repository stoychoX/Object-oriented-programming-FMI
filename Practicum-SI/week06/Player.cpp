#include "Player.h"
#include <cstring>
#include <iostream>
#pragma warning(disable:4996)

void Player::free()
{
	delete[] name;
	delete[] password;
	age = money = 0;
}

void Player::copyFrom(const Player& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	password = new char[strlen(other.password) + 1];
	strcpy(password, other.password);
	age = other.age;
	money = other.money;
}

Player::Player(const char* name, const char* pass, unsigned age, double money)
{
	if (name == nullptr)
	{
		std::cout << "Invalid name! Name set to \"default\"!" << std::endl;
		setName("default");
	}
	else
		setName(name);
	if (pass == nullptr)
	{
		std::cout << "Invalid pass! Pass set to \"default\"!" << std::endl;
		setPass("default");
	}
	else
		setPass(pass);
	this->age = age;
	this->money = money;
}

Player::Player(const Player& other)
{
	copyFrom(other);
}

Player& Player::operator=(const Player& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Player::~Player()
{
	free();
}

const char* Player::getName() const
{
	return name;
}
const char* Player::getPass() const
{
	return password;
}
unsigned Player::getAge() const
{
	return age;
}
double Player::getMoney() const
{
	return money;
}
void Player::setName(const char* name)
{
	if (name != nullptr)
	{
		delete[] this->name;
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
}
void Player::setPass(const char* pass)
{
	if (pass != nullptr)
	{
		this->password = new char[strlen(pass) + 1];
		strcpy(this->password, pass);
	}
}

void Player::setMoney(double money)
{
	this->money = money;
}

namespace
{
	void takeGuess(int& isEven, int& isPrime, int& isPowerOfTwo, int& number)
	{
		std::cout << "Enter 1(yes), 0(no) or -1(not answer):\n";
		std::cout << "Is number even: ";
		std::cin >> isEven;
		std::cout << "Is number prime: ";
		std::cin >> isPrime;
		std::cout << "Is number powerOfTwo: ";
		std::cin >> isPowerOfTwo;
		std::cout << "Try to guess the number or write -1:\n";
		std::cout << "The number is: ";
		std::cin >> number;
	}
}
Guess Player::guess() const
{
	int isEven, isPrime, isPowerOfTwo, number;
	takeGuess(isEven, isPrime, isPowerOfTwo, number);
	return Guess(isEven, isPrime, isPowerOfTwo, number);
}