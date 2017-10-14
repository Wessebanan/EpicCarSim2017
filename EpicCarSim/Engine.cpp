#include "Engine.h"

Engine::Engine()
{	
	this->gearChanged = false;
	this->currGear = 0; //0: Neutral, -1: Reverse.
	this->force = 0.f;
	this->engineBlown = false;
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

float Engine::getForce()
{
	return this->force;
}

int Engine::getGear()
{
	return this->currGear;
}

bool Engine::blown()
{
	return this->engineBlown;
}

void Engine::update(const Driver &driver, float velocity)
{
	float throttle = driver.getThrottle(); //[-1;1], negative throttle is brake.
	this->angVelocity = velocity * this->gearRatios[this->currGear + 1] * this->finalDriveRatio / this->radius;
	this->rpm = std::fabs(this->angVelocity) * 30.f / (float)M_PI;
	
	if (this->rpm < this->baseline)
	{
		this->rpm = this->baseline;
	}

	if (this->rpm < this->redline)
	{
		if (throttle > 0.005f)
		{
			this->torqueEngine = throttle * this->calcTorque();
		}
		else if(velocity > 0)//Engine brake.
		{
			this->torqueEngine = -this->brakeCoefficient * this->angVelocity / 60.f;
		}
		else
		{
			this->torqueEngine = 0;
		}
	}
	else
	{
		this->engineBlown = true;
	}
	this->torqueWheel = this->torqueEngine * this->gearRatios[currGear + 1] * this->finalDriveRatio;
	this->force = this->torqueWheel / this->radius;

	if (driver.getGearUp() && this->currGear < this->nGears)
	{
		this->currGear++;
	}
	else if (driver.getGearDown() && this->currGear > -1)
	{
		this->currGear--;
	}

}
