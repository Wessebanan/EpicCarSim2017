#ifndef CAR_H
#define CAR_H

//#include "Includes.h"
#include "Driver.h"
#include "Wheel.h"
#include "Engine.h"
#include "SFML\Graphics.hpp"
#define SCALE 0.000001

class Car : public sf::Drawable
{
protected:
	Wheel wheels[4];
	Engine* engine;
	float mass;
	float Cd;
	sf::RectangleShape dimensions;
	float height;
	float wheelDistance;

private:
	Driver driver;
	float velocity;
	sf::Vector2f direction;

	sf::Text rpmNgear;
	sf::Font arial;
public:
	Car();
	~Car();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setup(const int car, const int engine, const int wheels);
	void update(float gametime);
};

#endif