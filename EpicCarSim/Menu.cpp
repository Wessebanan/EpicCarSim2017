#include "Menu.h"

Menu::Menu(std::string cars[], std::string tires[], std::string courses[])
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

	int nOpts[] = { nCars, nTires, nCourses };
	int mostOpts = 0;
	for (int i = 0; i < 3; i++)
	{
		if (mostOpts < nOpts[i])
		{
			mostOpts = nOpts[i];
		}
	}


	for (int i = 0; i < nCars; i++)
	{
		this->carMenu[i].setString(cars[i]);
		this->carMenu[i].setFont(this->menuFont);
		this->carMenu[i].setCharacterSize(40);
		this->carMenu[i].setColor(sf::Color::Black);
		this->carMenu[i].setPosition(posVec);
		posVec.y += 70;
	}
	posVec.y = 220;
	for (int i = 0; i < nTires; i++)
	{
		this->tireMenu[i].setString(tires[i]);
		this->tireMenu[i].setFont(this->menuFont);
		this->tireMenu[i].setCharacterSize(40);
		this->tireMenu[i].setColor(sf::Color::Black);
		this->tireMenu[i].setPosition(posVec);
		posVec.y += 70;
	}
	posVec.y = 220;
	for (int i = 0; i < nCourses; i++)
	{
		this->courseMenu[i].setString(courses[i]);
		this->courseMenu[i].setFont(this->menuFont);
		this->courseMenu[i].setCharacterSize(40);
		this->courseMenu[i].setColor(sf::Color::Black);
		this->courseMenu[i].setPosition(posVec);
		posVec.y += 70;
	}
	posVec.y = 220;
	for(int i = 0; i < mostOpts; i++)
	{
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

Selects Menu::getSelects()
{
	return this->selects;
}

CurrentMenu Menu::getMenuState()
{
	return currMenu;
}


void Menu::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	target.draw(this->menuSprite, states);
	switch (this->currMenu)
	{
	case CAR:
		for (int i = 0; i < nCars; i++)
		{
			target.draw(this->carMenu[i], states);
		}
		break;
	case TIRE:
		for (int i = 0; i < nTires; i++)
		{
			target.draw(this->tireMenu[i], states);
		}
		break;
	case COURSE:
		for (int i = 0; i < nCourses; i++)
		{
			target.draw(this->courseMenu[i], states);
		}
		break;
	}
}

void Menu::update(sf::Window &window, float gameTime)
{
	if (this->onCooldown && this->cooldown < .2)
	{
		this->cooldown += gameTime;
	}
	else if (this->onCooldown && this->cooldown >= .2)
	{
		this->onCooldown = false;
		this->cooldown = 0;
	}
	
	if (!this->onCooldown)
	{
		switch (this->currMenu)
		{
		case CAR:
			for (int i = 0; i < nCars; i++)
			{
				if (this->clickBoxes[i].contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					this->onCooldown = true;
					this->selects.car = i;
					this->currMenu = TIRE;
				}
			}
			break;
		case TIRE:
			for (int i = 0; i < nTires; i++)
			{
				if (this->clickBoxes[i].contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					this->onCooldown = true;
					this->selects.tire = i;
					this->currMenu = COURSE;
				}
			}
			break;
		case COURSE:
			for (int i = 0; i < nCourses; i++)
			{
				if (this->clickBoxes[i].contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					this->onCooldown = true;
					this->selects.course = i;
					this->currMenu = NONE;
				}
			}	
			break;
		}
	}
}
