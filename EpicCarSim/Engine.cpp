#include "Engine.h"

Engine::Engine(enum CarType carType, float radius)
{	
	this->carType = carType;
	this->gearChanged = false;
	switch (this->carType)
	{
	case AUDI_R8:
		this->nGears = 7;
		this->gearRatios = new float[this->nGears + 2]; //+2 for neutral(0) and rev.
		
		this->gearRatios[0] = 2.647; //Rev
		this->gearRatios[1] = 0.000; //Neutral
		this->gearRatios[2] = 3.133;
		this->gearRatios[3] = 2.083;
		this->gearRatios[4] = 1.513;
		this->gearRatios[5] = 1.140;
		this->gearRatios[6] = 0.898;
		this->gearRatios[7] = 0.711;
		this->gearRatios[8] = 0.525;

		this->finalDriveRatio = 4.458;
		this->rpms = 1000; //Engine dies below.
		this->torqueTire = 0;
		this->torqueEngine = 285.337; //Base torque according to regression.
		this->power = 35; //Horsepower.
		this->angVelocity = this->rpms * 2 * M_PI / 60;
		
		this->currGear = 0; //0: Neutral, -1: Reverse.
	}
}

Engine::~Engine()
{
	delete[] this->gearRatios;
}

float Engine::calc()
{
	float newTorque = 0;
	float gearRatio = this->gearRatios[currGear + 1];
	//Calc max torque for given rpm.


	return newTorque;
}

float Engine::getTorque()
{
	return this->torqueTire;
}

float Engine::getRpms()
{
	return this->rpms;
}

float Engine::update(float gameTime, enum GearChange gearChange, float throttle, float velocity)
{
	//Update everything.

	
	torqueEngine = calc();
	
	switch (gearChange)
	{
	case UP:
		this->gearChanged = true;
		if (this->currGear < this->nGears)
		{
			this->currGear++;
		}
		break;
	case DOWN:
		this->gearChanged = true;
		if (this->currGear > -1)
		{
			this->currGear--;
		}
		break;
	case NONE:
		this->gearChanged = false;
		break;
	}
}
