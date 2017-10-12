#ifndef COURSE_H
#define COURSE_H

#include "SFML/Graphics.hpp"

class Course : public sf::Drawable
{
private:
	// The track to drive on
	sf::Texture trackTexture;
	sf::Sprite track;

	//  finish line and checkpoints
	// last one is finishLine
	sf::RectangleShape* checkpoints;
	int nrOfCheckpoints;
	int capacity;
	
	void increaseCapacity();

public:
	Course();
	~Course();
	virtual int init();

	// Get condition for the current position
	virtual int getCondition(const int x, const int y) = 0;

	const sf::Vector2f& getStartPosition();

	// Draw current track
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Texture& getTrackTexture();
	void setTrack(const sf::Texture _texture);
	void addCheckpoint(const sf::RectangleShape _checkpoint);
};

#endif
