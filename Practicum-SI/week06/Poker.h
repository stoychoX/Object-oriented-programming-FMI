#pragma once
#include "Player.h"

class Poker
{
	int rndNumber = 0; //0 - 100

	public:
		Poker() = default;
		void Play(Player& player);

};