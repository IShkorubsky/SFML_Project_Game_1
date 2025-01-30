#include "Game.h"

int main()
{
	//Initialize game engine
	Game game;

	while (game.isRunning())
	{
		//Initialize srand
		std::srand(static_cast<unsigned>(time(NULL)));

		//Update
		game.update();

		//Render
		game.render();
	}

    return 0;
}