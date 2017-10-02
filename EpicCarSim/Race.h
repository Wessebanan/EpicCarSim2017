#ifndef RACE_H
#define RACE_H

#include "SFML/Graphics.hpp"
#include "GrasslandCourse.h"

class Race : public sf::Drawable
{
private:
	Course* currentCourse;
	bool finished;

public:
	Race();
	~Race();
	void update();
	void setupRace(const int car, const int engine, const int wheels, const int course);
	bool endOfRace();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
