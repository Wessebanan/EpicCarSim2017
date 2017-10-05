#ifndef CAR_H
#define CAR_H

//#include "Includes.h"
#include "Driver.h"
#include "SFML\Graphics.hpp"

class Car : public sf::Drawable
{
private:
	/*
	Wheel wheels[4];
	Engine engine;
	*/
	Driver driver;

	float velocity;
	sf::Vector2f direction;


public:
	Car();
	~Car();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setup(const int car, const int engine, const int wheels);
	void update();
};

#endif