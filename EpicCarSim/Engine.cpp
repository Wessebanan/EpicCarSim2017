#include "Engine.h"

Engine::Engine()
{	
	this->gearChanged = false;
	this->currGear = 0; //0: Neutral, -1: Reverse.
	this->force = 0.f;
	this->engineBlown = false; //If rpm goes too high, the engine is destroyed.
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

	//Calculates angular velocity of the engine based on the velocity.
	this->angVelocity = velocity * this->gearRatios[this->currGear + 1] * this->finalDriveRatio / this->radius;
	this->rpm = std::fabs(this->angVelocity) * 30.f / (float)M_PI;
	
	if (this->rpm < this->baseline)
	{ //If the rpm is lower than the base rpm it is set to the base rpm.
		this->rpm = this->baseline;
	}

	if (this->rpm < this->redline)
	{
		//if (throttle > 0.005f)
		//{
		//	this->torqueEngine = throttle * this->calcTorque();
		//}
		//else if(velocity > 0)//Engine brake.
		//{
		//	this->torqueEngine = -this->brakeCoefficient * this->rpm / 60.f;
		//}
		//else
		//{
		//	this->torqueEngine = 0;
		//}

		//Calculates the torque of the engine, uses gross torque and adds engine brake.
		this->torqueEngine = std::max(throttle, 0.07f) * (this->calcTorque() + this->brakeCoefficient * this->rpm / 60.0f)
			- (this->gearRatios[this->currGear + 1] + 1.0f) / std::fabs(this->gearRatios[this->currGear + 1] + 1.0f) * this->brakeCoefficient * this->rpm / 60.0f;
	}
	else
	{
		this->engineBlown = true;
	}
	//Calculates the wheel torque and force based on current gear ratio, final drive ratio and wheel radius.
	this->torqueWheel = this->torqueEngine * this->gearRatios[this->currGear + 1] * this->finalDriveRatio;
	this->force = this->torqueWheel / this->radius;

	if (driver.getGearUp() && this->currGear < this->nGears) //Changes gear if the driver has requested it.
	{
		this->currGear++;
	}
	else if (driver.getGearDown() && this->currGear > -1)
	{
		this->currGear--;
	}

}
