#ifndef CAR_H
#define CAR_H

//#include "Includes.h"
#include "Driver.h"
#include "Wheel.h"
#include "Engine.h"
#include "SFML\Graphics.hpp"
#include <cmath>
#include "HiPerformanceWheel.h"
#define SCALE_FACTOR 5.f
#define SCALE sf::Vector2f(SCALE_FACTOR, SCALE_FACTOR)
#define ANGLE_CONVERSION 180 / M_PI
#define GRAVITY 9.82
#define TURN_SCALE 8.0f

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
	float brakeCoefficient;

private:
	Driver driver;
	float velocity;

	sf::Text rpmNgear;
	sf::Font arial;

	sf::Vector2f direction;
	sf::Transform trans;
	sf::Vector2f centripetDir;
	sf::Vector2f skidVelocity;

	float time;

public:
	Car(float width, float length);
	~Car();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float gametime, int condition); //0: grass, 1: dry asphalt, 2: wet asphalt.

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);

	float vecLength(sf::Vector2f vec);

	void setOrigin();

	bool engineBlown();
};

#endif