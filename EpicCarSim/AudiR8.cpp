#include "AudiR8.h"

AudiR8::AudiR8()
{
	this->engine		= new AudiR8Engine(/*this->wheels[0].getRadius()*/0.3f);
	this->Cd			= 0.36f;
	this->dimensions	= sf::RectangleShape(sf::Vector2f(2.04f, 4.43f));
	this->dimensions.setFillColor(sf::Color::Red);
	this->dimensions.setPosition(400, 400);
	this->height		= 1.24f;
	this->mass			= 1640.0f;
	this->wheelDistance = 2.65f;
}

AudiR8::~AudiR8()
{
}
