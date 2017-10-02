#ifndef GAME_H
#define GAME_H
#include "Race.h"
#include "SFML/Graphics.hpp"

enum GameState {
	race,
	menu
};

class Game
{
private:
	Race race;
	GameState currentState;

public:
	Game();
	~Game();
	void update();
	void render(sf::RenderWindow& window);
	void goToMenu();
	void goToRace();
};

#endif