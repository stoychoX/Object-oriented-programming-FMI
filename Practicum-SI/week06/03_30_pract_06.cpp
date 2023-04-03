#include <iostream>
#include "Poker.h"
#include <iostream>

//ne e pulna logikata za pokerGame.Play(player);
int main()
{
	Player player("Hari", "123", 19, 25);
	Poker pokerGame;

	if (player.canPlay())
		std::cout << "You're underaged." << std::endl;
		return 0;


	char* password;
	std::cin >> password;


	if (player.checkPassword(password))
	{
		pokerGame.Play(player);
	}
	else
	{
		std::cout << "Wrong password. Game ended!" << std::endl;
	}
}