#include <iostream>

#include "Game.hpp"

int main()
{
    std::cout << "Starting Game" << std::endl;

    Game * game = new Game();
		game->build();
		game->run();
		game->stop();
	delete game;
    return 0;
}



