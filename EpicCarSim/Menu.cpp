#include "Menu.h"

Menu::Menu()
{
	//Better font mayb? :thinking:
	if (!this->menuFont.loadFromFile("../Fonts/arial.ttf"))
	{
		std::cout << "Error: Menu font.";
	}

	if (!this->menuTex.loadFromFile("../Textures/menuTex.png"))
	{
		std::cout << "Error: Menu texture.";
	}
	this->menuSprite.setTexture(this->menuTex);

	sf::Vector2f posVec(450, 220);

	for (int i = 0; i < 5; i++)
	{
		//TODO: Give 'em names.
		this->carMenu[i].setString			(std::string("car ") + std::to_string(i+1));
		this->carMenu[i].setFont			(this->menuFont);
		this->carMenu[i].setCharacterSize	(40);
		this->carMenu[i].setColor			(sf::Color::Black);
		this->carMenu[i].setPosition		(posVec);

		this->wheelMenu[i].setString		(std::string("wheel ") + std::to_string(i + 1));
		this->wheelMenu[i].setFont			(this->menuFont);
		this->wheelMenu[i].setCharacterSize	(40);
		this->wheelMenu[i].setColor			(sf::Color::Black);
		this->wheelMenu[i].setPosition		(posVec);

		this->courseMenu[i].setString		(std::string("course ") + std::to_string(i + 1));
		this->courseMenu[i].setFont			(this->menuFont);
		this->courseMenu[i].setCharacterSize(40);
		this->courseMenu[i].setColor		(sf::Color::Black);
		this->courseMenu[i].setPosition		(posVec);
											
		this->engineMenu[i].setString		(std::string("engine ") + std::to_string(i + 1));
		this->engineMenu[i].setFont			(this->menuFont);
		this->engineMenu[i].setCharacterSize(40);
		this->engineMenu[i].setColor		(sf::Color::Black);
		this->engineMenu[i].setPosition		(posVec);
		
		this->clickBoxes[i].left	= 400;
		this->clickBoxes[i].top		= posVec.y;
		this->clickBoxes[i].height	= 40;
		this->clickBoxes[i].width	= 300;

		posVec.y += 70;
	}	

	this->currMenu = CAR;

	this->cooldown = 0;
	this->onCooldown = false;
}

Menu::~Menu()
{
}


void Menu::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	target.draw(this->menuSprite, states);
	switch (this->currMenu)
	{
	case CAR:
		for (int i = 0; i < 5; i++)
		{
			target.draw(this->carMenu[i], states);
		}
		break;
	case ENGINE:
		for (int i = 0; i < 5; i++)
		{
			target.draw(this->engineMenu[i], states);
		}
		break;
	case WHEEL:
		for (int i = 0; i < 5; i++)
		{
			target.draw(this->wheelMenu[i], states);
		}
		break;
	case COURSE:
		for (int i = 0; i < 5; i++)
		{
			target.draw(this->courseMenu[i], states);
		}
		break;
	}
}

void Menu::update(sf::Window &window, float gameTime)
{
	if (this->onCooldown && this->cooldown < 1)
	{
		this->cooldown += gameTime;
	}
	else if (this->onCooldown && this->cooldown >= .2)
	{
		this->onCooldown = false;
		this->cooldown = 0;
	}


	for (int i = 0; i < 5 && !this->onCooldown; i++)
	{
		if (this->clickBoxes[i].contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->onCooldown = true;
			
			switch (this->currMenu)
			{
			case CAR:
				this->carSelect = i;
				this->currMenu = ENGINE;
				break;
			case ENGINE:
				this->engineSelect = i;
				this->currMenu = WHEEL;
				break;
			case WHEEL:
				this->wheelSelect = i;
				this->currMenu = COURSE;
				break;
			case COURSE:
				this->courseSelect = i;
				this->currMenu = NONE;
				break;
			case NONE:
				//TODO: Switch state to race.
			}			
		}
	}
}
