#ifndef WHEEL_H
#define WHEEL_H
#include <SFML\Graphics.hpp>

class Wheel : public sf::Drawable
{
private:
	float radius;
public:
	float getRadius();
	float getFriction();

	void draw(sf::RenderTarget &target, sf::RenderStates states)const;
};

#endif