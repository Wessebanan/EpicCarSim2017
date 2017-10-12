#include "AudiR8Engine.h"

AudiR8Engine::AudiR8Engine(float radius)
	:Engine()
{
	this->nGears = 7;
	this->gearRatios = new float[this->nGears + 2]; //+2 for neutral(0) and rev.

	this->gearRatios[0] = -2.647f; //Rev
	this->gearRatios[1] = 0.000f; //Neutral
	this->gearRatios[2] = 3.133f;
	this->gearRatios[3] = 2.083f;
	this->gearRatios[4] = 1.513f;
	this->gearRatios[5] = 1.140f;
	this->gearRatios[6] = 0.898f;
	this->gearRatios[7] = 0.711f;
	this->gearRatios[8] = 0.525f;

	this->finalDriveRatio = 4.458f;
	this->rpm = 1000.f; //Engine dies below.
	this->torqueWheel = 0.f;
	this->torqueEngine = 285.337f; //Base torque according to regression.
	this->power = 35.f; //Horsepower.
	this->angVelocity = this->rpm * 2.f * (float)M_PI / 60.f;
	this->redline = 8300.0f;
	this->baseline = 1000.0f;

	this->breakCoefficient = 0.74f;

	this->radius = radius;
}

AudiR8Engine::~AudiR8Engine()
{
}

float AudiR8Engine::calcTorque()
{
	float newTorque = 0;
	
	newTorque = -0.000012f * pow(this->rpm, 2) + 0.137482f * this->rpm + 160.107f;
	

	return newTorque;
}

float AudiR8Engine::calcPower()
{
	return (35.0f + 0.08f * this->rpm) * 745.7f;
}
