#include "Game.h"
#include <iostream>
#pragma warning(disable : 4996)

Game::Game()
{
	generateNumberToGuess();
}

void Game::generateNumberToGuess()
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	int guess = std::rand();
	guess %= 100 + 1;
	numberToGuess = guess;
}

namespace
{
	bool areEven(int hasToBeEven, int numGen)
	{
		return !((numGen % 2 == 0)^hasToBeEven);
	}
	bool arePrime(int hasToBePrime, int numGen)
	{
		for (size_t i = 2; i < sqrt(numGen); i++)
		{
			if (numGen % i == 0)//the gen num is not prime
			{
				return !(0^hasToBePrime);
			}
		}
		return !(1^hasToBePrime);
	}

	bool arePowerOfTwo(int hasToBePowerOfTwo, int numGen)
	{
		return !(!((numGen - 1) & numGen))^hasToBePowerOfTwo;
	}

	bool areEqual(int numGuessed, int numGen)
	{
		return numGen == numGuessed;
	}
}

const unsigned COUNT_GUESSES = 4;
void Game::checkGuess(const Guess& guess, double entry) const
{
	static double coeficients[COUNT_GUESSES]{ 0.25, 0.5, 2, 10 };
	static bool(*predicate[4])(int numGuessed, int numGenerated) {areEven,arePrime, arePowerOfTwo, areEqual };
	for (size_t i = 0; i < COUNT_GUESSES; i++)
	{
		if (guess.guesses[i] != -1)
		{
			if (!predicate[i](guess.guesses[i], numberToGuess))//wrong guess
			{
				playerCurrentlyPlaying->setMoney(playerCurrentlyPlaying->getMoney() - entry < 0 ?
					0 : playerCurrentlyPlaying->getMoney() - entry);
				std::cout << "Sorry...Your " << i + 1 << " guess was wrong! The number was "
					<< numberToGuess << std::endl << "You lost " << entry << "lv.!\n";
			}
			else//right guess
			{
				double earning = entry * coeficients[i];
				playerCurrentlyPlaying->setMoney(playerCurrentlyPlaying->getMoney() + earning);
				std::cout << "Congrats! Your " << i + 1 << " guess was right! You won " << earning << "lv.!\n";
			}
		}
	}
	std::cout << "Your total money are " << playerCurrentlyPlaying->getMoney() << "lv. \n";
}

void Game::play(Player& player)
{
	std::cout << "Hello, " << player.getName() << "!\nTo play first enter your password: ";
	char pass[1024];
	std::cin >> pass;
	if (strcmp(player.getPass(), pass) == 0)
	{
		std::cout << "Entered successfully!\n";

		if (player.getAge() < 18)
		{
			std::cout << "Your age is under 18! You cannot play!\n";
			return;
		}
		playerCurrentlyPlaying = &player;
		std::cout << "Enter your capital:";
		double entry = 0;
		std::cin >> entry;
		if (entry > player.getMoney())
		{
			std::cout << "Not enough money! Your entry is now all of your money ("
				<<playerCurrentlyPlaying->getMoney()<<"lv.)!\n";
			entry = player.getMoney();
		}
		std::cout << "Time to play. Make your guess:\n";
		Guess guess = player.guess();
		checkGuess(guess, entry);
		std::cout << "End of game...\n";
	}
	else
	{
		std::cout << "Wrong password! Try again later!\n";
	}
}