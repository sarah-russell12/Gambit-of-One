/*
Entity.h

Sarah Russell

Date Last Updated: July 25, 2015

An Entity is an object within the gameworld that can or will be seen eventually
by the player.  Entities can move, be still, and interact with other Entities.

Updates:
- July 20, 2015: Declared the Entity class
- July 21, 2015: Added acceleration to functionality
- July 25, 2015: Added vital methods and stats related to gameplay
*/

#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "CommandQueue.h"
#include "SceneNode.h"

class Entity : public SceneNode
{
public:
	explicit		Entity(int hitpoints);

	void			repair(int points);
	void			damage(int points);
	void			destroy();

	int				getHitpoints() const;
	virtual bool	isDestroyed() const;

	void			setVelocity(sf::Vector2f velocity);
	void			setVelocity(float vx, float vy);
	sf::Vector2f	getVelocity() const;

	void			accelerate(sf::Vector2f velocity);
	void			accelerate(float vx, float vy);

protected:
	virtual void	updateCurrent(sf::Time dt, CommandQueue& commands);

private:
	sf::Vector2f	mVelocity;
	int				mHitpoints;
};

#endif //ENTITY_H