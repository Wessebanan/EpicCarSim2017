#include "AudiR8.h"

AudiR8::AudiR8() : Car(2.04f, 4.43f)
{
	this->wheels		= new HiPerformanceWheel(0.2413f);
	this->engine		= new AudiR8Engine(this->wheels->getRadius());
	this->Cd			= 0.36f; //Audi's own alleged Cd.
	this->dimensions.setFillColor(sf::Color::Red);
	this->height		= 1.24f;
	this->mass			= 1640.0f; //Mass of the car (without driver).
	this->wheelDistance = 2.65f; //Wheel base.
	this->area			= 2.01f; //Frontal area, for drag force calculations.
}

AudiR8::~AudiR8()
{
}
