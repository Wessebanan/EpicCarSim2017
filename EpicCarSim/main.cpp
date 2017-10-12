#include "Includes.h"
#include <crtdbg.h>

#define FPS_CAP_144 6.9444 //Milliseconds between frames.

//All data för bilen Audi R8 5.2 FSI Quattro 2017 hämtad från http://www.automobile-catalog.com/make/audi/r8_2/r8_2_1_coupe/2017.html

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	sf::RenderWindow window(sf::VideoMode(1600, 900), "EpicCarSim");

	sf::Clock timer; //To cap fps.

	while (window.isOpen())
	{
		if (timer.getElapsedTime().asMilliseconds() > FPS_CAP_144)
		{
			timer.restart();
			
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
					window.close();
			}

			game.update();

			window.clear();
			game.render(window);
			window.display();
		}
	}

	return 0;
}