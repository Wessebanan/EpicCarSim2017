#include "Includes.h"
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	sf::RenderWindow window(sf::VideoMode(800, 600), "EpicCarSim");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		game.update();

		window.clear();
		game.render(window);
		window.display();
	}

	return 0;
}