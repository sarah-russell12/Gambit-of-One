#ifndef ENTITY_H
#define ENTITY_H
#include "SFML_facilities.h"
#include "SceneNode.h"
#include "CommandQueue.h"


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