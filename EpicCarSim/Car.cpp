#include "Car.h"

Car::Car(float _width, float _length)
{
	this->velocity = 0.0f;
	this->arial.loadFromFile("../Fonts/arial.ttf");
	this->rpmNgear.setFont(this->arial);
	this->rpmNgear.setPosition(10, 10);
	this->rpmNgear.setColor(sf::Color::Black);
	this->rpmNgear.setCharacterSize(24);
	this->width = _width;
	this->length = _length;

	this->dimensions.setSize(sf::Vector2f(this->width, this->length));
	this->setOrigin();

	this->direction = sf::Vector2f(0.f, -1.f);
}

Car::~Car()
{
	if (this->engine)
	{
		delete this->engine;
		this->engine = nullptr;
	}
	if (this->wheels)
	{
		delete this->wheels;
		this->wheels = nullptr;
	}
}

void Car::setup(const int car, const int engine, const int wheels)
{

}

void Car::update(float gametime, int condition)
{
	this->driver.update();
	this->engine->update(this->driver, this->velocity);
	this->wheels->calcFriction(condition);
	
	float dragForce = 0.5f * 1.23f * this->area * this->Cd * pow(this->velocity, 2);	
	float frictionForce = 0.0f;
	float brakeForce = 0.0f;

	if (this->velocity > 0.5f || this->velocity < -0.5f)
	{
		frictionForce = this->mass * this->wheels->getRollingFriction() * 9.82f;
	}
	float maxForce = this->wheels->getSlidingFriction() * this->mass * GRAVITY;
	float force = this->engine->getThrust() - dragForce - frictionForce;
	if (force > maxForce)
	{
		force = maxForce;
	}
	else if (force < -maxForce)
	{
		force = -maxForce;
	}

	this->velocity += force / this->mass * gametime;
	
	float rotAngle = this->velocity * gametime * ANGLE_CONVERSION / this->length * sin(this->driver.getAxisX() * M_PI / 4);

	if ((this->velocity > 0.05f || this->velocity < -0.05f) && (rotAngle > 0.05f || rotAngle < -0.05f))
	{
		this->dimensions.rotate(rotAngle);
		this->trans.rotate(rotAngle);		
	}
	
	this->dimensions.move(trans.transformPoint(this->direction) * this->velocity * gametime);

	this->rpmNgear.setString(std::to_string(this->engine->getRpm()) + "\n" + std::to_string(this->engine->getGear()) + "\n" + std::to_string(this->velocity));
	
}

sf::Vector2f Car::getPosition()
{
	return sf::Vector2f(this->dimensions.getGlobalBounds().left + this->width / 2.f, this->dimensions.getGlobalBounds().top + this->height / 2.f);
}

void Car::setOrigin()
{
	this->dimensions.setOrigin(this->dimensions.getLocalBounds().width / 2.f, this->dimensions.getLocalBounds().height / 2.f);
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape temp = this->dimensions;
	temp.scale(sf::Vector2f(10.f, 10.f));
	target.draw(temp);
	target.draw(this->rpmNgear);
}