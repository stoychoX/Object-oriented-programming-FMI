#include <iostream>
#include "GamePlatform.h"

int main()
{
	GamePlatform gp(4);
	Game game1("Dragon city", 22.50);
	Game game2("Minecraft", 30.99);
	Game game3("GTA", 39);
	Game game4("Hello Kitty", 0.0);
	gp.addNewGameInStore(game1);
	gp.addNewGameInStore(game2);
	gp.addNewGameInStore(game3);
	gp.addNewGameInStore(game4);

	//available games
	gp.ShowAvailableGames();

	//free games
	unsigned countFreeGames = gp.getAllFreeGamesCount();
	Game* freeGames = gp.getAllFreeGames();
	std::cout << "Free games:" << std::endl;
	for (size_t i = 0; i < countFreeGames; i++)
	{
		freeGames[i].print();
	}

	//game index
	Game gameByIndex = gp.getGameByIndex(0);
	if (strcmp(gameByIndex.getTitle(), "no title") == 0)
	{
		std::cout << "No that index" << std::endl;
	}
	else
		gameByIndex.print();

	//cheapest game
	Game chGame = gp.getTheCheapestGame();
	chGame.print();

	//expensive game
	Game exGame = gp.getTheMostExpensiveGame();
	exGame.print();

	//add game - no space
	Game game5("Warriors", 50);
	gp.addNewGameInStore(game5);
	gp.ShowAvailableGames();

	//change capacity
	gp.setCapacity(5);

	//add game - new capacity
	gp.addNewGameInStore(game5);
	std::cout << "New capacity " << std::endl;
	gp.ShowAvailableGames();

	//safe into file
	gp.safeGamesIntoFile("Games.txt");

	//read from file
	unsigned length = 0;
	Game* gamesFromFile = gp.readGamesFromFile("Games.txt", length);
	std::cout << "Games form file:" << std::endl;
	for (size_t i = 0; i < length; i++)
	{
		gamesFromFile[i].print();
	}

	//one more type
	std::cout << "Final games: "<<std::endl;
	gp.setCapacity(6);
	Game game6("Super Mario", 10);
	gp.addNewGameInStore(game6);
	gp.safeGamesIntoFile("Games.txt");
	unsigned length2 = 0;
	Game* gamesFromFile2 = gp.readGamesFromFile("Games.txt", length2);
	for (size_t i = 0; i < length2; i++)
	{
		gamesFromFile2[i].print();
	}
	
	std::cout << (gp.removeGameByTitle("dsfwf")? "Deleted" : "No existing") << std::endl;
	std::cout << (gp.removeGameByTitle("Super Mario") ? "Deleted" : "No existing") << std::endl;
	std::cout << "Print: " << std::endl;
	gp.ShowAvailableGames();

	std::cout << "Print last: " << std::endl;
	gp.addNewGameInStore(game1);
	gp.ShowAvailableGames();

}