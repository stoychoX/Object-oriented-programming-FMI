#pragma once

class Player 
{
	char* name = nullptr;
	char* password = nullptr;
	unsigned int age = 0;
	double money = 0;

	void copyName(const char* newName);
	void copyPassword(const char* password);
	void copyFrom(const Player& other);
	void free();

	public:
		//big 4
		Player() = default;
		Player(const Player& other);
		Player& operator=(const Player& other);
		~Player();

		Player(const char* name, const char* password, unsigned int age, double money);
		bool canPlay();
		void changeName(const char* newName);
		bool checkPassword(const char* password);
};