#include "Race.h"

Race::Race()
{
	this->currentCourse = nullptr;
	this->finished = false;
	this->car = new AudiR8();
	this->gameOverTex.loadFromFile("Dead.bmp");
	this->gameOver.setTexture(this->gameOverTex);
}

Race::~Race()
{
	this->clean();
}

void Race::update(float gametime)
{
	this->car->update(gametime, this->currentCourse->getCondition(this->car->getPosition().x, this->car->getPosition().y));
	
	if (sf::Joystick::isButtonPressed(0, sf::Joystick::X) && this->car->engineBlown())
	{
		this->setup(0, 0, 0, 0);
	}
}

bool Race::endOfRace()
{
	return this->finished;
}

void Race::setup(const int car, const int engine, const int wheels, const int course)
{
	this->clean();
	this->setCourse(course);
	this->car = new AudiR8();
	this->car->setPosition(sf::Vector2f(24.f, 370.f));
	this->finished = false;
}

void Race::setCourse(const int course)
{
	if (course == GRASSLAND)
		this->currentCourse = new GrasslandCourse();
	else
		this->currentCourse = nullptr;

	this->currentCourse->init();
}

void Race::clean()
{
	if (this->currentCourse)
	{
		delete this->currentCourse;
		this->currentCourse = nullptr;
	}
	
	if (this->car)
	{
		delete this->car;
		this->car = nullptr;
	}
}

void Race::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!car->engineBlown())
	{ //Shows the game as long as the engine isn't broken.
		target.draw(*this->currentCourse);
		target.draw(*this->car);
	}
	else
	{
		target.draw(this->gameOver);
	}
}