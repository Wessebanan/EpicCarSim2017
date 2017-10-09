#include "AudiR8.h"

AudiR8::AudiR8() : Car(20.4f, 44.3f)
{
	this->engine		= new AudiR8Engine(/*this->wheels[0].getRadius()*/0.3f);
	this->Cd			= 0.36f;
	this->dimensions.setFillColor(sf::Color::Red);
	this->dimensions.setPosition(400, 400);
	this->height		= 1.24f;
	this->mass			= 1640.0f;
	this->wheelDistance = 2.65f;
	this->area			= 2.01f;
}

AudiR8::~AudiR8()
{
}
