#ifndef GAME_H
#define GAME_H

#include "Race.h"
#include "SFML/Graphics.hpp"

enum GameState {
	GS_RACE,
	GS_MENU
};

class Game
{
private:
	Race race;
	GameState currentState;
	sf::Clock gametime;

public:
	Game();
	~Game();
	void update();
	void render(sf::RenderWindow& window);
	void goToMenu();
	void goToRace();
};

#endif