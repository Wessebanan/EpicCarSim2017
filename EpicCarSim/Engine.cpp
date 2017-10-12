#include "Engine.h"

Engine::Engine()
{	
	this->gearChanged = false;
	this->currGear = 0; //0: Neutral, -1: Reverse.
	this->thrust = 0.f;
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

int Engine::getGear()
{
	return this->currGear;
}

void Engine::update(const Driver &driver, float velocity)
{
	//Update everything.
	
	this->angVelocity	= velocity * this->gearRatios[this->currGear + 1] * this->finalDriveRatio / this->radius;
	this->rpm			= this->angVelocity * 30.f / (float)M_PI;

	if (this->rpm < this->baseline)
	{
		this->rpm = this->baseline;
	}



	if (this->rpm < this->redline)
	{	
		this->torqueEngine = std::max(driver.getThrottle(), 0.01f) * this->calcTorque();//std::max to not have negative gas.
	}

	else
	{
		//Dead?
		this->torqueEngine = 0;
	}

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
