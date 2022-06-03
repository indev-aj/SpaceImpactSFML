#include "Game.h"

int main()
{
	srand(time(0));
	Game game;

	while (game.running() && !game.getEndGame()) {
	    // Update
	    game.update();

	    // Render
	    game.render();        
	}

	return 0;
}