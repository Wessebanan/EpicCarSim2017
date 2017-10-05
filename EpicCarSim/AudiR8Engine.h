#ifndef AUDI_R8_ENGINE
#define AUDI_R8_ENGINE
#include "Engine.h"

class AudiR8Engine : public Engine
{
private:
public:
	AudiR8Engine(float radius);
	~AudiR8Engine();

	float calcTorque();
	float calcPower();
};

#endif
