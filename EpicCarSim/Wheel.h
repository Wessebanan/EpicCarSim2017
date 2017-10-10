#ifndef WHEEL_H
#define WHEEL_H
#include <SFML\Graphics.hpp>

class Wheel : public sf::Drawable
{
protected:
	float radius;
	float rollingFriction;
	float slidingFriction;
	float brakeConstant;
public:
	Wheel(float radius);
	~Wheel();

	float getRadius();
	virtual void calcFriction(int condition) = 0;

	float getRollingFriction();
	float getSlidingFriction();

	void draw(sf::RenderTarget &target, sf::RenderStates states)const;
};

#endif