#include "Car.h"

Car::Car(float _width, float _length)
{
	// Initiate all general car variables
	this->velocity = 0.0f;												// Start Velocity
	this->arial.loadFromFile("../Fonts/arial.ttf");						// Font for rendering text
	this->rpmNgear.setFont(this->arial);								// Set up text output
	this->rpmNgear.setPosition(10, 10);
	this->rpmNgear.setColor(sf::Color::Black);
	this->rpmNgear.setCharacterSize(24);
	this->width = _width;												// Set width and lenght of car
	this->length = _length;

	this->dimensions.setSize(sf::Vector2f(this->length, this->width));	// Set the size dimensions of car
	this->setOrigin();													// Sets the origin point to middle of car

	this->direction = sf::Vector2f(1.f, 0.f);							// Start direction (Where the car is pointing)

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


void Car::update(float gametime, int condition)
{
	// Main car update function that updates every frame

	this->driver.update();									// Updates controller input from player
	this->engine->update(this->driver, this->velocity);		// Updates the engine

	float rollingFriction = 0;		// Default values in case we're standing still
	float dragForce = 0;
	float brakeForce = 0;
	float maxForce = this->wheels->getSlidingFriction() * this->mass * GRAVITY; // The maximum force using the friction force between tire and ground.

	if (std::fabs(this->velocity) > 0.05f)	// If we are currently not standing still, we calculate rolling friction and drag force
	{
		rollingFriction = -this->wheels->getRollingFriction() * GRAVITY * this->mass;
		dragForce = -0.5f * 1.23f * this->area * this->Cd * pow(this->velocity, 2);
	}

	if (this->driver.getThrottle() < 0 && this->velocity > 0) // If we're Activly Braking and in motion, we calculate the brake force
	{
		brakeForce = this->wheels->getSlidingFriction() * this->mass * GRAVITY * this->driver.getThrottle();
	}

	// Calculate the total force that affects the car
	float totalForce = this->engine->getForce() + rollingFriction + dragForce + brakeForce;
	

	// In case the total force is greater than the maximal force, the wheels skids
	if (totalForce > maxForce)
	{
		totalForce = maxForce;
	}

	
	// Get acceleration and apply to total velocity using elapsed time
	float acceleration = totalForce / this->mass;
	this->velocity += acceleration * gametime;
	

	this->dimensions.move(this->direction * this->velocity * gametime * SCALE_FACTOR);
	
	// Sets relevant car data into text to be displayed
	this->rpmNgear.setString(
		"RPM: " + std::to_string(std::floor(this->engine->getRpm()))
		+ "\nCurrent Gear: " + std::to_string(std::floor(this->engine->getGear()))
		+ "\nVelocity (km/h): " + std::to_string(std::floor(this->velocity*3.6f))
		+ "\nTotal Force: " + std::to_string(std::floor(totalForce))
		+ "\nEngine Force: " + std::to_string(std::floor(this->engine->getForce()))
		+ "\nBrake force: " + std::to_string(std::floor(brakeForce))
	);	
}

sf::Vector2f Car::getPosition()	// Gets the car current position
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