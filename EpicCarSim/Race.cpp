#include "Race.h"

Race::Race()
{
	this->currentCourse = nullptr;
	this->finished = false;
}

Race::~Race()
{
	if (this->currentCourse)
	{
		delete this->currentCourse;
		this->currentCourse = nullptr;
	}
}

void Race::update()
{
	this->car.update();
}

bool Race::endOfRace()
{
	return this->finished;
}

void Race::setup(const int car, const int engine, const int wheels, const int course)
{
	if (this->currentCourse)
	{
		delete this->currentCourse;
		this->currentCourse = nullptr;
	}

	this->currentCourse = new GrasslandCourse();
	this->currentCourse->init();
	this->finished = false;
}

void Race::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*this->currentCourse);
}