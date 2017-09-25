#ifndef INCLUDES_H
#define INCLUDES_H

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <fstream>
#include <math.h>
			   
#include "Car.h"
#include "Course.h"
#include "Driver.h"
#include "Game.h"
#include "Menu.h"
#include "Race.h"
#include "Wheel.h"
#include "Engine.h"


//Literally can't even

//#define N_CARS	 5
//#define N_ENGINES	 5
//#define N_WHEELS	 5
//#define N_COURSES	 5

enum Current_Menu
{
	CAR = 1,
	ENGINE = 2,
	WHEEL = 3,
	COURSE = 4,
	NONE = 5
};

#endif