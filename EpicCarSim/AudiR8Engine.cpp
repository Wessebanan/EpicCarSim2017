#include "AudiR8Engine.h"

AudiR8Engine::AudiR8Engine(float radius)
	:Engine(radius)
{
	this->nGears = 7;
	this->gearRatios = new float[this->nGears + 2]; //+2 for neutral(0) and rev.

	this->gearRatios[0] = -2.647; //Rev
	this->gearRatios[1] = 0.000; //Neutral
	this->gearRatios[2] = 3.133;
	this->gearRatios[3] = 2.083;
	this->gearRatios[4] = 1.513;
	this->gearRatios[5] = 1.140;
	this->gearRatios[6] = 0.898;
	this->gearRatios[7] = 0.711;
	this->gearRatios[8] = 0.525;

	this->finalDriveRatio = 4.458;
	this->rpm = 1000; //Engine dies below.
	this->torqueWheel = 0;
	this->torqueEngine = 285.337; //Base torque according to regression.
	this->power = 35; //Horsepower.
	this->angVelocity = this->rpm * 2 * M_PI / 60;
}

AudiR8Engine::~AudiR8Engine()
{
}

float AudiR8Engine::calcTorque()
{
	float newTorque = 0;

	if (1000 < this->rpm && this->rpm < 8300)
	{
		newTorque = -0.000012 * pow(this->rpm, 2) + 0.137482 * this->rpm + 160.107;
	}

	return newTorque;
}
