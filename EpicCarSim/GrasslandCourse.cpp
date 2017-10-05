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
	sf::Color grass(13, 188, 62);		
	sf::Color asphalt(176, 176, 176);
	sf::Color water(0, 151, 219);

	if (currentCondition == grass)
		returnValue = 0;

	else if (currentCondition == asphalt)
		returnValue = 1;

	else if (currentCondition == water)
		returnValue = 2;

	return returnValue;
}