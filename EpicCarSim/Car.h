#ifndef CAR_H
#define CAR_H

//#include "Includes.h"
#include "Driver.h"
#include "Wheel.h"
#include "Engine.h"
#include "SFML\Graphics.hpp"
#include <cmath>
#define SCALE 0.000001
#define ANGLE_CONVERSION 180 / M_PI

class Car : public sf::Drawable
{
protected:
	Wheel wheels[4];
	Engine* engine;
	float mass;
	float Cd;
	sf::RectangleShape dimensions;
	float height;
	float width;
	float length;
	float wheelDistance;
	float area;

private:
	Driver driver;
	float velocity;
	sf::RectangleShape direction;

	sf::Text rpmNgear;
	sf::Font arial;

	sf::RectangleShape testDir;
public:
	Car(float width, float length);
	~Car();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setup(const int car, const int engine, const int wheels);
	void update(float gametime);

	sf::Vector2f getPosition();

	void setOrigin();
};

#endif