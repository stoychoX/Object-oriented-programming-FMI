#include <iostream>
#include "Game.h"


int main()
{
    Player player1("Ivan", "123456", 18, 100);
    
    Game game;
    game.play(player1);
}

