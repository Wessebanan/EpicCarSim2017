#include "Course.h"

Course::Course()
{
	this->nrOfCheckpoints = 0;
	this->capacity = 1;
	this->checkpoints = new sf::RectangleShape[this->capacity];
}

Course::~Course()
{
	if (this->checkpoints)
	{
		delete[] this->checkpoints;
		this->checkpoints = nullptr;
	}
}

int Course::init()
{
	return 0;
}

void Course::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->track);
	for (int i = 0; i < this->nrOfCheckpoints; i++)
		target.draw(this->checkpoints[i]);
}

sf::Texture& Course::getTrackTexture()
{
	return this->trackTexture;
}

void Course::setTrack(const sf::Texture _texture)
{
	this->trackTexture = _texture;
	this->track.setTexture(this->trackTexture);
}

void Course::addCheckpoint(const sf::RectangleShape _checkpoint)
{
	if (this->capacity == this->nrOfCheckpoints)
		this->increaseCapacity();

	this->checkpoints[this->nrOfCheckpoints++] = _checkpoint;
}

void Course::increaseCapacity()
{
	sf::RectangleShape* temp = new sf::RectangleShape[++this->capacity];
	
	for (int i = 0; i < this->nrOfCheckpoints; i++)
		temp[i] = this->checkpoints[i];
	
	delete[] this->checkpoints;
	this->checkpoints = temp;
}

const sf::Vector2f& Course::getStartPosition()
{
	return sf::Vector2f(this->checkpoints[0].getPosition().x + (this->checkpoints[0].getGlobalBounds().width * 4), this->checkpoints[0].getPosition().y + this->checkpoints[0].getGlobalBounds().height / 2);
}
