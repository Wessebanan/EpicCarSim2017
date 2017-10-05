#ifndef RACE_H
#define RACE_H

#include "SFML/Graphics.hpp"
#include "GrasslandCourse.h"
#include "AudiR8.h"

#define GRASSLAND 0

class Race : public sf::Drawable
{
private:
	Course* currentCourse;
	bool finished;
	Car* car;

	void clean();

public:
	Race();
	~Race();
	void update(float gametime);
	void setup(const int car, const int engine, const int wheels, const int course);
	void setCourse(const int course);
	bool endOfRace();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
