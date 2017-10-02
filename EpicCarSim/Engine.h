#ifndef ENGINE_H
#define ENGINE_H
#include"Includes.h"
class Engine : public sf::Drawable
{
private:
	float rpms;
	float torqueWheel;
	float torqueEngine;
	float power; //P
	float angVelocity; //OmegaE
	
	float mass;

	float finalDriveRatio; //G
	int nGears;
	float* gearRatios; //g for every gear.
	int currGear;
public:
	Engine(float mass, int nGears, float g[], float G);
	~Engine();

	float calcTorque(float throttle);
	float getTorque();
	float getMass();
	float getRpms();

	void update(enum GearChange gearChange, float throttle);	
};

#endif