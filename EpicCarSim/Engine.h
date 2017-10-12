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
	float breakCoefficient;

	bool gearChanged;

	float thrust; 

public:
	Engine();
	~Engine();

	virtual float calcTorque() = 0; //Returns the maximum torque at current rpm.
	virtual float calcPower() = 0;
	float getTorque();
	float getRpm();
	float getThrust();
	int getGear();

	void update(const Driver &driver, float velocity);
};

#endif