#include "Engine.h"

Engine::Engine(float mass, int nGears, float g[], float G)
{
	this->mass = mass;
	this->nGears = nGears;
	this->gearRatios = new float[this->nGears];
	for (int i = 0; i < this->nGears; i++)
	{
		this->gearRatios[i] = g[i];
	}
	this->finalDriveRatio = G;

	this->rpms = 0;
	this->torqueWheel = 0;
	this->torqueEngine = 0;
	this->power = 0;
	this->angVelocity = 0;

	this->currGear = 1;
}

Engine::~Engine()
{
	delete[] this->gearRatios;
}

float Engine::calcTorque(float throttle)
{
	float newTorque = 0;
	//Torquestuff.
	return newTorque;
}

float Engine::getTorque()
{
	return this->torqueWheel;
}

float Engine::getMass()
{
	return this->mass;
}

float Engine::getRpms()
{
	return this->rpms;
}

void Engine::update(GearChange gearChange, float throttle)
{
	this->torqueWheel = calcTorque(throttle);
	switch (gearChange)
	{
	case UP:
		if (this->currGear < this->nGears)
		{
			this->currGear++;
		}
		break;
	case DOWN:
		if (this->currGear > 0)
		{
			this->currGear--;
		}
		break;
	case NONE:
		break;
	}
}
