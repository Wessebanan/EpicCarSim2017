#include "Car.h"

Car::Car(float _width, float _length)
{

	this->direction.setPosition(0.0f, 0.5f);	
	//this->direction.setOrigin(0.0f, 0.0f);

	this->velocity = 0.0f;
	this->arial.loadFromFile("../Fonts/arial.ttf");
	this->rpmNgear.setFont(this->arial);
	this->rpmNgear.setPosition(10, 10);
	this->rpmNgear.setColor(sf::Color::Black);
	this->rpmNgear.setCharacterSize(24);
	this->width = _width;
	this->length = _length;

	this->dimensions.setSize(sf::Vector2f(this->width, this->length));
	//this->setOrigin();
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
	
	float dragForce = 0.5f * 1.23f *  this->area * this->Cd * pow(this->velocity, 2);	
	float frictionForce = this->mass * 0.014f * 9.82f;	

	float force = this->engine->getThrust() - dragForce - frictionForce;
	//if (force < 0.f)
	//{
	//	force = 0.f;
	//}

	this->velocity += force / this->mass * gametime;

	if (this->velocity != 0)
	{
		this->dimensions.rotate(this->velocity * gametime * ANGULAR_CONVERSION / this->length * sin(this->driver.getAxisX() * M_PI / 4));
	}
	this->direction.setRotation(this->dimensions.getRotation() + this->driver.getAxisX() * 45.f);
	
	float x = (this->direction.getTransform().transformPoint(this->direction.getPosition())).x;
	float y = (this->direction.getTransform().transformPoint(this->direction.getPosition())).y;

	std::cout << x << std::endl << y << std::endl << driver.getAxisX() << std::endl << std::endl;
	this->dimensions.move(this->direction.getTransform().transformPoint(this->direction.getPosition()) * this->velocity * gametime);
	this->rpmNgear.setString(std::to_string(this->engine->getRpm()) + "\n" + std::to_string(this->engine->getGear()));
	
}

sf::Vector2f Car::getPosition()
{
	return this->dimensions.getPosition();
}

void Car::setOrigin()
{
	this->dimensions.setOrigin(this->dimensions.getLocalBounds().width / 2.f, this->dimensions.getLocalBounds().height / 2.f);
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape temp = this->dimensions;
	//temp.scale(sf::Vector2f(10, 10));
	target.draw(temp);
	target.draw(this->rpmNgear);
}