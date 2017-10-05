#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H

const int nCars		= 4;
const int nTires	= 2;
const int nCourses	= 1;

struct Selects
{
	unsigned int car;
	unsigned int tire;
	unsigned int course;
};

enum CurrentMenu
{
	CAR		= 1,
	TIRE	= 2,
	COURSE	= 3,
	NONE	= 4
};

enum CarType 
{
	AUDI_R8 = 0
};

#endif
