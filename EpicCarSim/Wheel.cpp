#include "Wheel.h"

Wheel::Wheel(float radius)
{
	this->radius = radius;
	this->rollingFriction = 0.014f;
	this->slidingFriction = 1.0f;
}

Wheel::~Wheel()
{
}

float Wheel::getRadius()
{
	return this->radius;
}

float Wheel::getRollingFriction()
{
	return this->rollingFriction;
}

float Wheel::getSlidingFriction()
{
	return this->slidingFriction;
}

void Wheel::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}
