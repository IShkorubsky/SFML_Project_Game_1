#include "Game.h"

int main()
{
	//Initialize game engine
	Game game;

	while (game.isRunning())
	{
		//Update
		game.update();

		//Render
		game.render();
	}

    return 0;
}