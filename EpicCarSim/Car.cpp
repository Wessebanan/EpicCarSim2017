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

	this->dimensions.setSize(sf::Vector2f(this->length, this->width));
	this->setOrigin();

	this->direction = sf::Vector2f(1.f, 0.f);

	this->time = 0.0f;
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

float Car::turnFunction()
{
	float turnValue = this->driver.getAxisX();

	if (this->velocity <= 5.0f)
		return turnValue;

	else if (this->velocity <= 80.0f)
		return turnValue - 0.012f * this->velocity * turnValue;

	else
		return turnValue * 0.1f;

}

void Car::update(float gametime, int condition)
{
	this->driver.update();
	this->engine->update(this->driver, this->velocity);

	float rollingFriction = 0;
	float dragForce = 0;
	float brakeForce = 0;
	float maxForce = this->wheels->getSlidingFriction() * this->mass * GRAVITY; //The friction force between tire and ground.

	if (std::fabs(this->velocity) > 0.05f)
	{
		rollingFriction = -this->wheels->getRollingFriction() * GRAVITY * this->mass;
		dragForce = -0.5f * 1.23f * this->area * this->Cd * pow(this->velocity, 2);
	}
	if (this->driver.getThrottle() < 0 && this->velocity > 0) //Active braking.
	{
		brakeForce = this->wheels->getSlidingFriction() * this->mass * GRAVITY * this->driver.getThrottle();
	}
	float totalForce = this->engine->getForce() + rollingFriction + dragForce + brakeForce;
	
	
	if (totalForce > maxForce) //Wheel spin.
	{
		totalForce = maxForce;
	}

	if (this->velocity > 0)
	{
		this->time += gametime;
	}
	if(this->time > 3.5f)
	{ 
		bool good = true;
	}
	
	float acceleration = totalForce / this->mass;
	this->velocity += acceleration * gametime;
	
	this->dimensions.move(this->direction * this->velocity * gametime * SCALE_FACTOR);
	
	this->rpmNgear.setString(
		"RPM: " + std::to_string(this->engine->getRpm())
		+ "\nCurrent Gear: " + std::to_string(this->engine->getGear())
		+ "\nVelocity (m/s): " + std::to_string(this->velocity)
		+ " / " + std::to_string(this->velocity*3.6f)
		+ "\nTotal Force: " + std::to_string(totalForce)
		+ "\nEngine Force: " + std::to_string(this->engine->getForce())
		+ "\nVelocity: " + std::to_string(this->velocity)
		+ "\nThrottle: " + std::to_string(this->driver.getThrottle())
		+ "\nBrake force: " + std::to_string(brakeForce)
	);	
}

sf::Vector2f Car::getPosition()
{
	return sf::Vector2f((this->dimensions.getGlobalBounds().left + this->width / 2.f) * SCALE_FACTOR, (this->dimensions.getGlobalBounds().top + this->height / 2.f) * SCALE_FACTOR);
}

void Car::setPosition(sf::Vector2f position)
{
	this->dimensions.setPosition(position);
}

float Car::vecLength(sf::Vector2f vec)
{	
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

void Car::setOrigin()
{
	this->dimensions.setOrigin(this->dimensions.getLocalBounds().width / 2.f, this->dimensions.getLocalBounds().height / 2.f);
}

bool Car::engineBlown()
{
	return this->engine->blown();
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape temp = this->dimensions;
	temp.scale(SCALE);
	target.draw(temp);
	target.draw(this->rpmNgear);
}