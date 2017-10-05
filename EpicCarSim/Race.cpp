#include "Race.h"

Race::Race()
{
	this->currentCourse = nullptr;
	this->finished = false;
}

Race::~Race()
{
	this->clean();
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
	this->setCourse(course);
	this->finished = false;
}

void Race::setCourse(const int course)
{
	this->clean();

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
}

void Race::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*this->currentCourse);
}