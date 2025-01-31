#include "Game.h"

int main()
{
	//Initialize srand
	std::srand(static_cast<unsigned>(time(0)));

	//Initialize game engine
	Game game;

	while (game.isRunning() && !game.getEndGame())
	{
		//Update
		game.update();

		//Render
		game.render();
	}

    return 0;
}