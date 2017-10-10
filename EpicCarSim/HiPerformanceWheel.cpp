#include "HiPerformanceWheel.h"

HiPerformanceWheel::HiPerformanceWheel(float radius)
	:Wheel(radius)
{
	this->brakeConstant = 0.62;
}

HiPerformanceWheel::~HiPerformanceWheel()
{
}

void HiPerformanceWheel::calcFriction(int condition)
{
	switch (condition)
	{
	case 0: //Grass. (Data from "dry earth road")
		this->slidingFriction = 0.55f;
		this->rollingFriction = 0.08f;
	case 1: //Dry asphalt.
		this->slidingFriction = 1.00f;
		this->rollingFriction = 0.014f;
	case 2: //Wet asphalt.
		this->slidingFriction = 0.70f;
		this->rollingFriction = 0.014f;
	}
}
