#include <string>
#include <fstream>
#include "GamePlatform.h"

GamePlatform::GamePlatform() : GamePlatform::GamePlatform(0)
{}

GamePlatform::GamePlatform(unsigned capacity)
{
	this->setCapacity(capacity);
	this->games = new Game[this->getCapacity()];
}

GamePlatform::~GamePlatform()
{
	delete[] this->games;
}

unsigned GamePlatform::getGamesCount() const
{
	return this->currGamesCount;
}

unsigned GamePlatform::getCapacity() const
{
	return this->capacity;
}

//That func where?
void CopyArraysFromTo(Game* source, unsigned sourceLen, Game* dest, unsigned destLen)
{
	if (sourceLen <= destLen)
	{
		for (size_t i = 0; i < sourceLen; i++)
		{
			dest[i] = source[i];
		}
	}
}

void GamePlatform::setCapacity(unsigned newCapacity)
{
	if (newCapacity > this->getCapacity())
	{
		Game* oldGamesPtr = this->games;
		Game* gamesNew = new Game[newCapacity];
		CopyArraysFromTo(this->games, this->getCapacity(), gamesNew, newCapacity);
		this->capacity = newCapacity;
		this->games = gamesNew;
		delete[] oldGamesPtr;
	}
}

bool GamePlatform::addNewGameInStore(const Game& game)
{
	if (this->getGamesCount() < this->getCapacity())
	{
		this->games[this->getGamesCount()] = game;
		this->currGamesCount++;
		return true;
	}
	return false;
}

Game GamePlatform::getGameByIndex(unsigned index) const
{
	if (index < this->getGamesCount())
	{
		return this->games[index];
	}
	//that ok?
	//or return false
	//or exeption
	return Game();
}

Game* GamePlatform::getAllGames() const
{
	Game* games = new Game[this->getGamesCount()];
	for (size_t i = 0; i < this->getGamesCount(); i++)
	{
		games[i] = this->getGameByIndex(i);
	}
	return games;
}

//How to implement it?
//
//-1 -> is cheaper
//+1 -> is more expensive
//
//enum
//
//pointer to function
Game getGameBy(int indexCriteria)
{
	Game game;
	return game;
}

Game GamePlatform::getTheCheapestGame() const
{
	Game chGame;
	if (this->getGamesCount() == 0)
	{
		return chGame;
	}
	chGame = this->getGameByIndex(0);
	for (size_t i = 1; i < this->getGamesCount(); i++)
	{
		Game currGame = this->getGameByIndex(i);
		if (chGame.getPrice() > currGame.getPrice())
		{
			chGame = currGame;
		}
	}
	return chGame;
}

Game GamePlatform::getTheMostExpensiveGame() const
{
	Game exGame;
	if (this->getGamesCount() == 0)
	{
		return exGame;
	}
	exGame = this->getGameByIndex(0);
	for (size_t i = 1; i < this->getGamesCount(); i++)
	{
		Game currGame = this->getGameByIndex(i);
		if (exGame.getPrice() < currGame.getPrice())
		{
			exGame = currGame;
		}
	}
	return exGame;
}

unsigned GamePlatform::getAllFreeGamesCount() const
{
	unsigned count = 0;
	for (size_t i = 0; i < this->currGamesCount; i++)
	{
		if (this->getGameByIndex(i).isFree())
		{
			count++;
		}
	}return count;
}

Game* GamePlatform::getAllFreeGames() const
{
	unsigned countFreeGames = this->getAllFreeGamesCount();
	if (countFreeGames == 0)
	{
		return nullptr;
	}
	Game* freeGames = new Game[countFreeGames];
	unsigned indexFreeGame = 0;
	for (size_t i = 0; i < this->getGamesCount(); i++)
	{
		Game currGame = this->getGameByIndex(i);
		if (currGame.isFree())
		{
			freeGames[indexFreeGame++] = currGame;
		}
	}
	return freeGames;
}

bool GamePlatform::removeGameByTitle(const char* title)
{
	for (size_t i = 0; i < this->getGamesCount(); i++)
	{
		Game currGame = this->getGameByIndex(i);
		if (strcmp(currGame.getTitle(), title) == 0)
		{
			//swap function?
			Game lastGameInList = this->getGameByIndex(this->getGamesCount() - 1);
			this->games[i] = lastGameInList;
			games[this->getGamesCount() - 1] = currGame;
			this->currGamesCount -= 1;
			return true;
		}
	}
	return false;
}

bool safeGameIntoFile(std::ofstream& ofs, const Game& game)
{
	if (!ofs.is_open())
	{
		return false;
	}
	unsigned titleLen = strlen(game.getTitle());
	ofs << titleLen << " ";
	ofs << game.getTitle() << " ";
	ofs << game.getPrice();
	ofs << std::endl;
	return true;
}

bool GamePlatform::safeGamesIntoFile(const char* fileName) const
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open())
	{
		return false;
	}

	ofs << this->getGamesCount() << std::endl;
	//is that correct?
	//ofs << this->games;
	for (size_t i = 0; i < this->getGamesCount(); i++)
	{
		if (!safeGameIntoFile(ofs, this->getGameByIndex(i)))
		{
			ofs.close();
			return false;
		}
	}
	ofs.close();
	return true;
}

Game readGame(std::ifstream& ifs)
{
	if (!ifs.is_open())
	{
		Game gameErr;
		return gameErr;
	}

	unsigned titleLen=0;
	ifs >> titleLen;
	ifs.ignore();

	char* gameTitle = new char[titleLen + 1];
	unsigned index = 0;
	for (size_t i = 0; i < titleLen; i++)
	{
		gameTitle[index++] = ifs.get();
	}
	gameTitle[titleLen] = '\0';
	ifs.ignore();

	
	double gamePrice = 0;
	ifs >> gamePrice;
	ifs.ignore();

	Game game(gameTitle, gamePrice);
	return game;
}
Game* GamePlatform::readGamesFromFile(const char* fileName, unsigned& countGames)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		return nullptr;
	}

	ifs >> countGames;
	ifs.ignore();
	if (countGames == 0)
	{
		ifs.close();
		return nullptr;
	}

	Game* games = new Game[countGames];
	for (size_t i = 0; i < countGames; i++)
	{
		games[i] = readGame(ifs);
	}

	ifs.close();
	return games;
}

void GamePlatform::ShowAvailableGames() const
{
	for (size_t i = 0; i < this->getGamesCount(); i++)
	{
		Game game = this->getGameByIndex(i);
		if (game.isGameAvailable())
		{
			game.print();
		}
	}
}
