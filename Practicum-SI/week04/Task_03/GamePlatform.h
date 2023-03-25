#pragma once
#include "Game.h"

class GamePlatform
{
private:
	Game* games;
	unsigned capacity = 0;
	unsigned currGamesCount = 0;

public:
	GamePlatform();
	GamePlatform(unsigned capacity);
	~GamePlatform();
	unsigned getGamesCount() const;
	unsigned getCapacity() const;
	void setCapacity(unsigned capacity);
	bool addNewGameInStore(const Game& game);
	Game getGameByIndex(unsigned index) const;
	Game* getAllGames() const;
	Game getTheCheapestGame() const;
	Game getTheMostExpensiveGame() const;
	unsigned getAllFreeGamesCount() const;
	Game* getAllFreeGames() const;
	bool removeGameByTitle(const char* title);
	bool safeGamesIntoFile(const char* fileName) const;
	Game* readGamesFromFile(const char* fileName, unsigned& countGames);
	void ShowAvailableGames() const;
};