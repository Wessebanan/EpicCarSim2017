#include "Race.h"

Race::Race()
{
	this->currentCourse = nullptr;
	this->finished = false;
	this->car = new AudiR8();
}

Race::~Race()
{
	this->clean();

	if (this->car)
	{
		delete this->car;
		this->car = nullptr;
	}
}

void Race::update(float gametime)
{
	this->car->update(gametime/*, this->currentCourse->getCondition(this->car.get*/);
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
	target.draw(*this->car);
}