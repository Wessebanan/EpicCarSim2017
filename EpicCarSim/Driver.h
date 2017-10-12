#ifndef DRIVER_H
#define DRIVER_H
#include<SFML\Window\Joystick.hpp>
#include<SFML\Window\Keyboard.hpp>
#define _USE_MATH_DEFINES
#include<math.h>
#include <iostream>

#define TOTAL_BUTTONS 8
#define DEAD_ZONE 0.25f

class Driver
{
private:
	const enum keyboard_keys : unsigned int {
		A =			sf::Keyboard::Z,
		B =			sf::Keyboard::X,
		START =		sf::Keyboard::Escape,
		GEAR_DOWN = sf::Keyboard::A,
		GEAR_UP =	sf::Keyboard::S,
		UP =		sf::Keyboard::Up,
		DOWN =		sf::Keyboard::Down,
		LEFT =		sf::Keyboard::Left,
		RIGHT =		sf::Keyboard::Right
	};
	const enum controller_keys : unsigned int {
		x_axis = sf::Joystick::X,
		y_axis = sf::Joystick::Y,
		trigger = sf::Joystick::Z,
		gear_down = 4,
		gear_up = 5
	};
	
public:
	Driver() {};
	virtual ~Driver() {};

	void update();
	float getThrottle()const;
	float getAxisX()const;
	bool getGearDown()const;
	bool getGearUp()const;

private:
	float x, y, rotation, length, acceleration;
	char gear;
	void updateJoystick();
	void updateKeyboard();
};

#endif