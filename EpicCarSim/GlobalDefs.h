#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H

const int nCars = 4;
const int nWheels = 2;
const int nCourses = 1;
const int nEngines = 3;

struct Selects
{
	unsigned int car;
	unsigned int wheel;
	unsigned int course;
	unsigned int engine;
};

enum CurrentMenu
{
	CAR = 1,
	ENGINE = 2,
	WHEEL = 3,
	COURSE = 4,
	NONE = 5
};

#endif
