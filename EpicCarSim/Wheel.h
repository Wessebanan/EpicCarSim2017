#ifndef WHEEL_H
#define WHEEL_H
#include"Includes.h"
class Wheel : public sf::Drawable
{
private:

public:
	float getRadius();
	float getFriction();

	void draw(sf::RenderTarget &target, sf::RenderStates states);
};

#endif