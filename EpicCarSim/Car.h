#ifndef CAR_H
#define CAR_H

//#include "Includes.h"
#include "Driver.h"
#include "Wheel.h"
#include "Engine.h"
#include "SFML\Graphics.hpp"
#include <cmath>
#include "HiPerformanceWheel.h"
#define SCALE 10
#define ANGLE_CONVERSION 180 / M_PI
#define GRAVITY 9.82

class Car : public sf::Drawable
{
protected:
	Wheel* wheels;
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

	sf::Text rpmNgear;
	sf::Font arial;

	sf::Vector2f direction;
	sf::Transform trans;
public:
	Car(float width, float length);
	~Car();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setup(const int car, const int engine, const int wheels);
	void update(float gametime, int condition); //0: grass, 1: dry asphalt, 2: wet asphalt.

	sf::Vector2f getPosition();

	void setOrigin();
};

#endif