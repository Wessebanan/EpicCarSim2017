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

	//this->dimensions.setPosition(10, 370);
	this->dimensions.setSize(sf::Vector2f(this->length, this->width));
	this->setOrigin();

	this->direction = sf::Vector2f(1.f, 0.f);
	//this->centripetDir = sf::Vector2f(1.f, 0.f);
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
	this->wheels->calcFriction(condition);

	//float turn = 0.0f;
	//sf::Vector2f forwardForce = this->engine->getThrust() * this->direction; //Thrust force in car direction.
	//sf::Vector2f sidewaysForce(0.f, 0.f);

	float rollingFriction = 0;
	float dragForce = 0;
	float brakeForce = 0;
	float maxForce = this->wheels->getSlidingFriction() * this->mass * GRAVITY; //The friction force between tire and ground.

	if (std::fabs(this->velocity) > 0.05f)
	{
		//turn = this->turnFunction();
		rollingFriction = -this->wheels->getRollingFriction() * GRAVITY * this->mass;
		dragForce = -0.5f * 1.23f * this->area * this->Cd * pow(this->velocity, 2);
	}
	if (this->driver.getThrottle() < 0 && this->velocity > 0) //Active braking.
	{
		brakeForce = this->brakeCoefficient * this->mass * GRAVITY * this->driver.getThrottle();
	}
	float totalForce = this->engine->getForce() + rollingFriction + dragForce + brakeForce;

	//if (totalForce <= 1.0f)
	//	totalForce = 1.0f;
	//float angle = this->velocity * sin(turn * M_PI / 4.f) * gametime / this->length;
	//float forwardForce = this->direction * totalForce * cos(angle);
	//sf::Vector2f sidewaysForce = this->centripetDir * totalForce * sin(angle)*/
	//if ((this->driver.getAxisX() < -0.05f || this->driver.getAxisX() > 0.05f) && (this->velocity > 0.05f || this->velocity < -0.05f))
	//{ //TODO: non-instant turning.
	//	float radius = this->length / sin(-this->driver.getAxisX() * M_PI / 4); //Turning radius if turning.
	//	sidewaysForce = (this->mass * pow(this->velocity, 2) / radius) * this->centripetDir; //Centripetal force if turning.
	//}		
	//if (this->vecLength(sidewaysForce) > maxForce)
	//{
	//	sidewaysForce = maxForce * sidewaysForce / vecLength(sidewaysForce);
	
	
	if (totalForce > maxForce) //Wheel spin.
	{
		totalForce = maxForce;
	}



	//sf::Vector2f resultingForce = forwardForce + sidewaysForce;
	//sf::Vector2f acceleration = forwardForce / this->mass;
	//sf::Vector2f velocityVec = this->direction * this->velocity;
	//velocityVec += acceleration * gametime;							//TODO: change sign based on direction of force.

	float acceleration = totalForce / this->mass;
	this->velocity += acceleration * gametime;
	

	this->dimensions.move(this->direction * this->velocity * gametime * SCALE_FACTOR);
	
	//this->velocity = this->vecLength(velocityVec);// *sign;
	//if (std::fabs(turn) > 0.05f && std::fabs(this->velocity) > 0.05f)
	//{
	//	float rotation = -1.0f * turn / abs(turn) * acos(this->direction.x * resultingForce.x / this->vecLength(resultingForce) + this->direction.y * resultingForce.y / this->vecLength(resultingForce));
	//	this->dimensions.rotate(angle * 180 / M_PI * -1.0f);
	//	//this->trans.rotate(angle * 180 / M_PI * -1.0f);
	//	this->direction = totalForce / std::fabs(totalForce) * resultingForce / totalForce;
	//	this->centripetDir = sf::Vector2f(this->direction.y, -this->direction.x);
	//}
	//float rotAngle = this->velocity * gametime * ANGLE_CONVERSION / this->length * sin(this->driver.getAxisX() * M_PI / 4.f);
	//if ((this->velocity > 0.05f || this->velocity < -0.05f) && (rotAngle > 0.05f || rotAngle < -0.05f))
	//{
	//	this->dimensions.rotate(rotAngle);
	//	this->trans.rotate(rotAngle);
	//}
	//float dragForce = 0.5f * 1.23f * this->area * this->Cd * pow(this->velocity, 2);	
	//float frictionForce = 0.0f;
	//float brakeForce = 0.0f;
	//if (this->velocity > 0.5f || this->velocity < -0.5f)
	//{
	//	frictionForce = this->mass * this->wheels->getRollingFriction() * GRAVITY;
	//}
	//float maxForce = this->wheels->getSlidingFriction() * this->mass * GRAVITY;
	//float force = this->engine->getThrust() - dragForce - frictionForce;
	//if (force > maxForce)
	//{
	//	force = maxForce;
	//}
	//else if (force < -maxForce)
	//{
	//	force = -maxForce;
	//}
	//this->velocity += (force / this->mass) * gametime;
	//
	//float rotAngle = this->velocity * gametime * ANGLE_CONVERSION / this->length * sin(this->driver.getAxisX() * M_PI / 4.f);
	//float radius = this->length / sin(this->driver.getAxisX() * M_PI / 4);
	//
	//float centripetForce = this->mass * pow(this->velocity, 2) / radius;
	//if ((this->velocity > 0.05f || this->velocity < -0.05f) && (rotAngle > 0.05f || rotAngle < -0.05f))
	//{
	//	this->dimensions.rotate(rotAngle);
	//	this->trans.rotate(rotAngle);		
	//}
	//if ((this->driver.getAxisX() > 0.05f) && (this->driver.getAxisX() < -0.05f))
	//{
	//	this->dimensions.move(radius * cos(this->driver.getAxisX() * M_PI / 4.f), radius * sin(this->driver.getAxisX() * M_PI / 4.f));
	//}	
	//
	//this->dimensions.move(trans.transformPoint(this->direction) * this->velocity * SCALE_FACTOR * gametime);

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