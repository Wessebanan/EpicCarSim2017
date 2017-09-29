#include"Includes.h"
#include<Windows.h>

int main()
{
	//Game game;
	Driver driver;
	while (1)
	{
		driver.update();
		Sleep(300);
	}
	//game.run();
	/*while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}*/
	return 0;
}