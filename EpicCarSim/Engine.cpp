#include "Engine.h"

Engine::Engine(float radius)
{	
	this->carType = carType;
	this->gearChanged = false;
	this->currGear = 0; //0: Neutral, -1: Reverse.
	this->thrust = 0;
}

Engine::~Engine()
{
	delete[] this->gearRatios;
}

float Engine::getTorque()
{
	return this->torqueWheel;
}

float Engine::getRpm()
{
	return this->rpm;
}

float Engine::getThrust()
{
	return this->thrust;
}

void Engine::update(float gameTime, const Driver &driver, float velocity)
{
	//Update everything.
	
	this->angVelocity	= velocity / this->radius;
	this->rpm			= this->angVelocity * 60 / 2 * M_PI;
	this->torqueEngine	= driver.getThrottle() * this->calcTorque();
	this->torqueWheel	= this->torqueEngine * this->gearRatios[currGear + 1] * this->finalDriveRatio;
	this->thrust		= this->torqueWheel / this->radius;

	if (driver.getGearUp() && this->currGear < this->nGears)
	{
		this->currGear++;
	}
	else if (driver.getGearDown() && this->currGear > -1)
	{
		this->currGear--;
	}
}
