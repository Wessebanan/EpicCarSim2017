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
	tempTrack.loadFromFile("GrasslandCourse1600x900.bmp");
	this->setTrack(tempTrack);

	// add checkpoints
	sf::RectangleShape sf;
	sf.setFillColor(sf::Color());
	sf.setSize(sf::Vector2f(10, 220));

	sf.setPosition(900, 665);
	this->addCheckpoint(sf);

	return 0;
}

int GrasslandCourse::getCondition(const int x, const int y)
{
	int returnValue = -1;
	sf::Color currentCondition = this->getTrackTexture().copyToImage().getPixel(x, y);

	// What color each condition have (to compare against) 
	sf::Color grass(14, 209, 69);		
	sf::Color asphalt(88, 88, 88);
	sf::Color water(0, 151, 219);

	if (currentCondition == grass)
		returnValue = 0;

	else if (currentCondition == asphalt)
		returnValue = 1;

	else if (currentCondition == water)
		returnValue = 2;

	return returnValue;
}