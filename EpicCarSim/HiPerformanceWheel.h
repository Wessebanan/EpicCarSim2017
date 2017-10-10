#ifndef HI_PERFORMANCE_WHEEL_H
#define HI_PERFORMANCE_WHEEL_H

#include "Wheel.h"

class HiPerformanceWheel : public Wheel
{
private:
public:
	HiPerformanceWheel(float radius);
	~HiPerformanceWheel();

	void calcFriction(int condition);
};

#endif