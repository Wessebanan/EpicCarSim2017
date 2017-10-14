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

	this->dimensions.setPosition(400, 400);
	this->dimensions.setSize(sf::Vector2f(this->width, this->length));
	this->setOrigin();

	this->direction = sf::Vector2f(0.f, -1.f);
	this->centripetDir = sf::Vector2f(1.f, 0.f);
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

	float turn = 0.0f;
	//sf::Vector2f forwardForce = this->engine->getThrust() * this->direction; //Thrust force in car direction.
	//sf::Vector2f sidewaysForce(0.f, 0.f);

	float rollingFriction = 0;
	float dragForce = 0;
	if (std::fabs(this->velocity) > 0.05f)
	{
		turn = this->turnFunction();
		rollingFriction = -this->wheels->getRollingFriction() * GRAVITY * this->mass;
		dragForce = -0.5f * 1.23f * this->area * this->Cd * pow(this->velocity, 2);
	}
	float totalForce = this->engine->getThrust() + rollingFriction + dragForce;

	if (totalForce <= 1.0f)
		totalForce = 1.0f;

	float angle = this->velocity * sin(turn * M_PI / 4.f) * gametime / this->length;


	sf::Vector2f forwardForce = this->direction * totalForce * cos(angle);
	
	sf::Vector2f sidewaysForce = this->centripetDir * totalForce * sin(angle);

	//if ((this->driver.getAxisX() < -0.05f || this->driver.getAxisX() > 0.05f) && (this->velocity > 0.05f || this->velocity < -0.05f))
	//{ //TODO: non-instant turning.
	//	float radius = this->length / sin(-this->driver.getAxisX() * M_PI / 4); //Turning radius if turning.
	//	//sidewaysForce = (this->mass * pow(this->velocity, 2) / radius) * this->centripetDir; //Centripetal force if turning.
	//}	

	float maxForce = this->wheels->getSlidingFriction() * this->mass * GRAVITY;
	if (this->vecLength(sidewaysForce) > maxForce)
	{
		sidewaysForce = maxForce * sidewaysForce / vecLength(sidewaysForce);
	} //TODO: sliding shit
	if (this->vecLength(forwardForce) > maxForce)
	{
		forwardForce = maxForce * forwardForce / vecLength(forwardForce);
	}



	sf::Vector2f resultingForce = forwardForce + sidewaysForce;
	sf::Vector2f acceleration = resultingForce / this->mass;

	sf::Vector2f velocityVec = this->direction * this->velocity;

	velocityVec += acceleration * gametime;							//TODO: change sign based on direction of force.


	this->dimensions.move(trans.transformPoint(velocityVec) * gametime * SCALE_FACTOR);
	this->velocity = this->vecLength(velocityVec);// *sign;

	if (std::fabs(turn) > 0.05f && std::fabs(this->velocity) > 0.05f)
	{
		float rotation = -1.0f * turn / abs(turn) * acos(this->direction.x * resultingForce.x / this->vecLength(resultingForce) + this->direction.y * resultingForce.y / this->vecLength(resultingForce));
		this->dimensions.rotate(angle * 180 / M_PI * -1.0f);
		//this->trans.rotate(angle * 180 / M_PI * -1.0f);

		this->direction = totalForce / std::fabs(totalForce) * resultingForce / totalForce;
		this->centripetDir = sf::Vector2f(this->direction.y, -this->direction.x);
	}

	/*float rotAngle = this->velocity * gametime * ANGLE_CONVERSION / this->length * sin(this->driver.getAxisX() * M_PI / 4.f);
	if ((this->velocity > 0.05f || this->velocity < -0.05f) && (rotAngle > 0.05f || rotAngle < -0.05f))
	{
		this->dimensions.rotate(rotAngle);
		this->trans.rotate(rotAngle);
	}*/

	/*float dragForce = 0.5f * 1.23f * this->area * this->Cd * pow(this->velocity, 2);	
	float frictionForce = 0.0f;
	float brakeForce = 0.0f;

	if (this->velocity > 0.5f || this->velocity < -0.5f)
	{
		frictionForce = this->mass * this->wheels->getRollingFriction() * GRAVITY;
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

	this->velocity += (force / this->mass) * gametime;
	
	float rotAngle = this->velocity * gametime * ANGLE_CONVERSION / this->length * sin(this->driver.getAxisX() * M_PI / 4.f);
	float radius = this->length / sin(this->driver.getAxisX() * M_PI / 4);
	
	float centripetForce = this->mass * pow(this->velocity, 2) / radius;



	if ((this->velocity > 0.05f || this->velocity < -0.05f) && (rotAngle > 0.05f || rotAngle < -0.05f))
	{
		this->dimensions.rotate(rotAngle);
		this->trans.rotate(rotAngle);		
	}
	if ((this->driver.getAxisX() > 0.05f) && (this->driver.getAxisX() < -0.05f))
	{
		this->dimensions.move(radius * cos(this->driver.getAxisX() * M_PI / 4.f), radius * sin(this->driver.getAxisX() * M_PI / 4.f));
	}	
	
	this->dimensions.move(trans.transformPoint(this->direction) * this->velocity * SCALE_FACTOR * gametime);*/

	this->rpmNgear.setString(
		"RPM: " + std::to_string(this->engine->getRpm())
		+ "\nCurrent Gear: " + std::to_string(this->engine->getGear())
		+ "\nVelocity (m/s): " + std::to_string(this->velocity)
		+ " / " + std::to_string(this->velocity*3.6f)
		+ "\nTotal Force: " + std::to_string(totalForce)
		+ "\nEngine Thrust: " + std::to_string(this->engine->getThrust())
		+ "\nTurning angle: " + std::to_string(angle * 180 / M_PI)
		+ "\n VecVelocity: " + std::to_string(velocityVec.x) + " " + std::to_string(velocityVec.y)
		+ "\n Drag Force: " + std::to_string(dragForce)
		+ "\n Rolling Friction: " + std::to_string(rollingFriction)
		+ "\n Acceleration: " + std::to_string(acceleration.x) + " " + std::to_string(acceleration.y)
		+ "\n Velocity: " + std::to_string(this->velocity)
		+ "\n Direction: " + std::to_string(direction.x) + " " + std::to_string(direction.y)
		
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

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape temp = this->dimensions;
	temp.scale(SCALE);
	target.draw(temp);
	target.draw(this->rpmNgear);
}