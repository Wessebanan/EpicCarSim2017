#include "GrasslandCourse.h"

GrasslandCourse::GrasslandCourse() 
	: Course()
{
}

GrasslandCourse::~GrasslandCourse()
{
}

int GrasslandCourse::init()
{
	// set track
	sf::Texture tempTrack;
	tempTrack.loadFromFile("GrasslandCourse.bmp");
	this->setTrack(tempTrack);

	// add checkpoints
	sf::RectangleShape sf;
	sf.setFillColor(sf::Color());
	sf.setSize(sf::Vector2f(10, 110));

	sf.setPosition(370, 490);
	this->addCheckpoint(sf);

	return 0;
}

int GrasslandCourse::getCondition(const int x, const int y)
{
	int returnValue = 0;
	sf::Color currentCondition = this->getTrackTexture().copyToImage().getPixel(x, y);

	// What color each condition have (to compare against) 
	sf::Color grass(255, 255, 255);		// Has to be decided
	sf::Color asphalt(0, 0, 0);			

	if (currentCondition == grass)
		returnValue = 1;

	else if (currentCondition == asphalt)
		returnValue = 2;

	return returnValue;
}