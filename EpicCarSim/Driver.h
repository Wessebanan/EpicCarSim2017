#ifndef DRIVER_H
#define DRIVER_H
#include"Includes.h"
#include<SFML\Window\Joystick.hpp>
#include<SFML\Window\Keyboard.hpp>
#define _USE_MATH_DEFINES
#include<math.h>

#define TOTAL_BUTTONS 8
#define DEAD_ZONE 0.25f

class Driver
{
private:
	const enum keyboard_keys : unsigned int {
		A =			sf::Keyboard::Z,
		B =			sf::Keyboard::X,
		START =		sf::Keyboard::Escape,
		SELECT =	sf::Keyboard::LShift,
		UP =		sf::Keyboard::Up,
		DOWN =		sf::Keyboard::Down,
		LEFT =		sf::Keyboard::Left,
		RIGHT =		sf::Keyboard::Right
	};
	const enum controller_keys : unsigned int {
		x_axis = sf::Joystick::X,
		y_axis = sf::Joystick::Y,
		trigger = sf::Joystick::Z,
		gear_down = 0,
		gear_up = 1
	};
	
public:
	Driver() {};
	virtual ~Driver() {};

	void update() {
		this->gear <<= 2;
		this->updateJoystick();


		/*
		std::cout << "x: " << this->x << std::endl
			<< "y: " << this->y << std::endl
			<< "Rotation: " << this->rotation << std::endl
			<< "Lenght: " << this->length << std::endl;
		*/

		/*
		std::cout << "Connected: " << (sf::Joystick::isConnected(0) ? "Yes" : "No") << std::endl
			<< "X: " << sf::Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl
			<< "Y: " << sf::Joystick::getAxisPosition(0, sf::Joystick::Y) << std::endl;
		*/
	}
	float getThrottle() { return 0.f; };

private:
	float x, y, rotation, length, acceleration;
	char gear;
	void updateJoystick();
	void updateKeyboard();
};

#endif