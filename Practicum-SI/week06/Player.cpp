#include "Player.h"
#include <cstring>

bool Player::checkPassword(const char* password)
{
	return strcmp(this->password, password);
}

bool Player::canPlay()
{
	return age >= 18;
}

void Player::changeName(const char* newName)
{
	copyName(newName);
}

Player::Player(const char* name, const char* password, unsigned int age, double money)
{
	copyName(name);
	copyPassword(password);
	this->age = age;
	this->money = money;
}

void Player::copyName(const char* newName)
{
	name = new char[strlen(newName) + 1];
	strcpy(name, newName);
}

void Player::copyPassword(const char* newPassword)
{
	password = new char[strlen(newPassword) + 1];
	strcpy(password, newPassword);
}

void Player::copyFrom(const Player& otherPlayer)
{
	copyName(otherPlayer.name);
	copyPassword(otherPlayer.password);
	age = otherPlayer.age;
	money = otherPlayer.money;
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
void Player::free()
{
	delete[] name;
	delete[] password;
	name = nullptr;
	password = nullptr;
	age = 0;
	money = 0;
}