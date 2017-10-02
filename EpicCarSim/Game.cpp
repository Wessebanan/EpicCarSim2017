#include "Game.h"

Game::Game() 
{
	// Which state to go to
	this->goToRace();
}

Game::~Game() 
{

}

void Game::update()
{
	switch (this->currentState)
	{

	case GameState::menu:
			break;


	case GameState::race:
			this->race.update();

			if (this->race.endOfRace())
				this->goToMenu();
		break;
	}
}

// Change state to menu
void Game::goToMenu()
{
	this->currentState = GameState::menu;
}

// Change state to race
void Game::goToRace()
{
	this->currentState = GameState::race;
	this->race.setupRace(0, 0, 0, 0);
}

void Game::render(sf::RenderWindow& window)
{
	switch (this->currentState)
	{
	case GameState::menu:
		break;

	case GameState::race:
		window.draw(this->race);
		break;

	}
}