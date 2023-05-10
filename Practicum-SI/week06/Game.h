#pragma once
#include "Player.h"

class Game
{
	unsigned numberToGuess = -1;
	void generateNumberToGuess();
	void checkGuess(const Guess& guess, double entry) const;
	Player* playerCurrentlyPlaying = nullptr;
public:
	Game();
	void play(Player& player);
};