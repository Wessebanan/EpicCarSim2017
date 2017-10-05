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

	case GameState::GS_MENU:
			break;


	case GameState::GS_RACE:
			this->race.update();

			if (this->race.endOfRace())
				this->goToMenu();
		break;
	}
}

// Change state to menu
void Game::goToMenu()
{
	this->currentState = GameState::GS_MENU;
}

// Change state to race
void Game::goToRace()
{
	this->currentState = GameState::GS_RACE;
	this->race.setup(0, 0, 0, 0);
}

void Game::render(sf::RenderWindow& window)
{
	switch (this->currentState)
	{
	case GameState::GS_MENU:
		break;

	case GameState::GS_RACE:
		window.draw(this->race);
		break;

	}
}