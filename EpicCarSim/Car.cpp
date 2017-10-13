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
	this->centripetDir = sf::Vector2f(-1.f, 0.f);
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
	
	sf::Vector2f forwardForce = this->engine->getThrust() * this->direction; //Thrust force in car direction.
	sf::Vector2f sidewaysForce(0.f, 0.f);
	if (this->driver.getAxisX() < -0.05f || this->driver.getAxisX() > 0.05f)
	{ //TODO: non-instant turning.
		float radius = this->length / sin(this->driver.getAxisX() * M_PI / 4); //Turning radius if turning.
		sidewaysForce = (this->mass * pow(this->velocity, 2) / radius) * this->centripetDir; //Centripetal force if turning.
	}	
	float maxForce = this->wheels->getSlidingFriction() * this->mass * GRAVITY;

	if (this->vecLength(sidewaysForce) > maxForce)
	{
		sidewaysForce = maxForce * sidewaysForce / vecLength(sidewaysForce);
	} //TODO: sliding shit
	if (this->vecLength(forwardForce) > maxForce)
	{
		forwardForce = maxForce * forwardForce / vecLength(forwardForce);
	}
	
	sf::Vector2f totalForce = forwardForce + sidewaysForce + (0.5f * 1.23f * this->area * this->Cd * pow(this->velocity, 2)) * -1.f * this->direction; //Drag force.

	sf::Vector2f acceleration = totalForce / this->mass;
	sf::Vector2f velocityVec = this->direction * this->velocity;
	velocityVec += acceleration * gametime; //TODO: change sign based on direction of force.
	this->velocity = sqrt(pow(velocityVec.x, 2) + pow(velocityVec.y, 2));

	this->dimensions.move(velocityVec * gametime * SCALE_FACTOR);

	if (this->driver.getAxisX() < -0.05f || this->driver.getAxisX() > 0.05f)
	{
		this->direction = velocityVec / velocity;
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

	this->rpmNgear.setString("RPM: " + std::to_string(this->engine->getRpm()) 
							+ "\nCurrent Gear: " + std::to_string(this->engine->getGear()) 
							+ "\nVelocity (m/s): " + std::to_string(this->velocity) 
							+ " / " + std::to_string(this->velocity*3.6f) + "\nTotal Force: " 
							+ std::to_string(sqrt(pow(totalForce.x, 2) + pow(totalForce.y, 2))) 
							+ "\nEngine Thrust: " + std::to_string(this->engine->getThrust()));
	
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