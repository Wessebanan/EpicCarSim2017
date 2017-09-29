#include "Driver.h"
#define KEYDOWN(x) sf::Keyboard::isKeyPressed((sf::Keyboard::Key)x)
void Driver::updateJoystick()
{
	sf::Joystick::update();
	this->x = sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)controller_keys::x_axis) / 100.f;
	this->y = sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)controller_keys::y_axis) / 100.f;
	this->length = sqrtf(powf(this->x, 2.f) + powf(this->y, 2.f));
	if (this->length < DEAD_ZONE)
	{
		this->x = this->y = this->length = this->rotation = 0.f;
	}
	else {
		this->rotation = tanhf(this->x / this->y)*(float)M_PI;
	}

	this->acceleration = sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)controller_keys::trigger) / 100.f; // JOYSTICK R DOESN'T WORK FOR ME :<

	//this->gear |= (sf::Joystick::isButtonPressed(0,0) ? 
}

void Driver::updateKeyboard()
{
	//this->x_axis = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)LEFT) ? 1.0f : 
	this->x = KEYDOWN(keyboard_keys::RIGHT) ? 1.0f : KEYDOWN(keyboard_keys::LEFT) ? -1.0f : 0.0f;
	this->y = KEYDOWN(keyboard_keys::UP) ? 1.0f : KEYDOWN(keyboard_keys::DOWN) ? -1.0f : 0.0f;
	this->acceleration = KEYDOWN(keyboard_keys::A) ? 1.0f : 0.0f;
}
