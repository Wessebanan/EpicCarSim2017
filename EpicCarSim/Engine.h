#ifndef ENGINE_H
#define ENGINE_H
#include"Includes.h"
class Engine
{
private:
	enum CarType carType;

	float rpms;
	float torqueTire;
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

public:
	Engine(enum CarType carType, float radius);
	~Engine();

	float calc(); //Returns the maximum torque at current rpm.
	float getTorque();
	float getRpms();

	float update(float gameTime, enum GearChange gearChange, float throttle, float velocity);
};

#endif