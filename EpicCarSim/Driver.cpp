#include "Driver.h"
#define KEYDOWN(x) sf::Keyboard::isKeyPressed((sf::Keyboard::Key)x)
void Driver::update()
{
	this->gear <<= 2;
	if (sf::Joystick::isConnected(0))
		this->updateJoystick();
	else
		this->updateKeyboard();
}
float Driver::getThrottle()const
{
	return this->acceleration;
}
float Driver::getAxisX()const
{
	return -this->x;
}
bool Driver::getGearDown()const
{
	return !(this->gear & 0x8) && (this->gear & 0x2);
}
bool Driver::getGearUp()const
{
	return !(this->gear & 0x4) && (this->gear & 0x1);
}
bool Driver::isApressed() const
{
	return sf::Joystick::isButtonPressed(0, sf::Joystick::X);
}
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
	else 
	{
		this->rotation = tanhf(this->x / this->y)*(float)M_PI;
	}

	this->acceleration = sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)controller_keys::trigger) / -100.f;

	this->gear |= (sf::Joystick::isButtonPressed(0, controller_keys::gear_down) ? 0x2 : 0x0) |
		(sf::Joystick::isButtonPressed(0, controller_keys::gear_up) ? 0x1 : 0x0);

}

void Driver::updateKeyboard()
{
	this->x = KEYDOWN(keyboard_keys::RIGHT) ? 1.0f : KEYDOWN(keyboard_keys::LEFT) ? -1.0f : 0.0f;
	this->y = KEYDOWN(keyboard_keys::UP) ? 1.0f : KEYDOWN(keyboard_keys::DOWN) ? -1.0f : 0.0f;
	this->acceleration = KEYDOWN(keyboard_keys::A) ? 1.0f : 0.0f;

	this->gear |= (KEYDOWN(keyboard_keys::GEAR_DOWN) ? 0x2 : 0x0) |
		(KEYDOWN(keyboard_keys::GEAR_UP) ? 0x1 : 0x0);
}
