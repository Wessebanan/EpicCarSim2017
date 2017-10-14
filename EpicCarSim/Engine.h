#ifndef ENGINE_H
#define ENGINE_H

#include "Driver.h"
class Engine
{
private:

protected:
	float rpm;
	float torqueWheel;
	float torqueEngine;
	float angVelocity; //Engine.
	float power;
	float velocity;
	float radius; //Wheel.

	float redline;
	float baseline;

	float finalDriveRatio; //G
	int nGears;
	float* gearRatios; //g for every gear.
	int currGear;
	float brakeCoefficient;

	bool gearChanged;
	bool engineBlown;

	float force; 

public:
	Engine();
	~Engine();

	virtual float calcTorque() = 0; //Returns the maximum torque at current rpm.
	virtual float calcPower() = 0;
	float getTorque();
	float getRpm();
	float getForce();
	int getGear();
	bool blown();

	void update(const Driver &driver, float velocity);
};

#endif