#ifndef RACE_H
#define RACE_H

#include "SFML/Graphics.hpp"
#include "GrasslandCourse.h"
#include "Car.h"

class Race : public sf::Drawable
{
private:
	Course* currentCourse;
	bool finished;
	Car car;

public:
	Race();
	~Race();
	void update();
	void setup(const int car, const int engine, const int wheels, const int course);
	bool endOfRace();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
