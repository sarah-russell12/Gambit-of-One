/*
Entity.h

Date Last Updated: June 20, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use "facilities" header files anymore
*/

#ifndef ENTITY_H
#define ENTITY_H

#include "CommandQueue.h"
#include "SceneNode.h"
#include "SFML_facilities.h"

class Entity : public SceneNode
{
public:
					Entity(int hitPoints);

	void			setVelocity(sf::Vector2f velocity);
	void			setVelocity(float vx, float vy);
	void			accelerate(sf::Vector2f velocity);
	void			accelerate(float vx, float vy);
	sf::Vector2f	getVelocity() const;

	int				getHitpoints() const;
	virtual bool	isDestroyed() const;
	void			repair(int points);
	void			damage(int points);
	void			destroy();
	virtual void	updateCurrent(sf::Time dt, CommandQueue& commands);

private:
	sf::Vector2f	mVelocity;
	int				mHitPoints;
};

#endif //ENTITY_H