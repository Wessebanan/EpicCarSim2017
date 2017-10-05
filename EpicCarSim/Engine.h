#ifndef ENGINE_H
#define ENGINE_H
#include"Includes.h"
class Engine
{
private:

protected:
	enum CarType carType;

	float rpm;
	float torqueWheel;
	float torqueEngine;
	float angVelocity; //Engine.
	float power;
	float velocity;
	float radius; //Wheel.

	float finalDriveRatio; //G
	int nGears;
	float* gearRatios; //g for every gear.
	int currGear;

	bool gearChanged;

	float thrust; 

public:
	Engine(float radius);
	~Engine();

	virtual float calcTorque() = 0; //Returns the maximum torque at current rpm.
	float getTorque();
	float getRpm();
	float getThrust();

	void update(float gameTime, const Driver &driver, float velocity);
};

#endif