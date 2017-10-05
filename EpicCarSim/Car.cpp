#include "Car.h"

Car::Car()
{
	this->direction = sf::Vector2f(1.0f, 0.0f);
	this->velocity = 0.0f;
	this->arial.loadFromFile("../Fonts/arial.ttf");
	this->rpmNgear.setFont(this->arial);
	this->rpmNgear.setPosition(100, 100);
	this->rpmNgear.setColor(sf::Color::Black);
	this->rpmNgear.setCharacterSize(24);
	
}

Car::~Car()
{
	if (this->engine)
	{
		delete this->engine;
		this->engine = nullptr;
	}
}

void Car::setup(const int car, const int engine, const int wheels)
{

}

void Car::update(float gametime)
{
	this->driver.update();
	this->engine->update(this->driver, this->velocity);
	this->velocity += this->engine->getThrust() / this->mass * gametime;
	this->dimensions.move(this->direction * this->velocity * .001f);
	this->rpmNgear.setString(std::to_string(engine->getRpm()) + "\n" + std::to_string(this->engine->getGear()));

}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape temp = this->dimensions;
	temp.scale(sf::Vector2f(10, 10));
	target.draw(temp);
	target.draw(this->rpmNgear);
}