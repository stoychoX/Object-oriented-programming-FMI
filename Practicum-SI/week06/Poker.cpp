#include "Poker.h"
#include "Util.h"
#include <random>
#include <iostream>

void Poker::Play(Player& player)
{
	srand(time(NULL));
	while (true)
	{
		rndNumber = 1 + (rand() % 100);
		unsigned int playerNum;
		std::cin >> playerNum;

		//kak da dam na usera da izbere nqkoq ot opciite, nqkuv enum li trqbva da polzvam?
	}
}