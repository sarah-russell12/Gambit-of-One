/*
Entity.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

An Entity is an object within the gameworld that can or will be seen eventually
by the player.  Entities can move, be still, and interact with other Entities.
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SceneNode.hpp"

class Entity : public SceneNode
{
public:

	enum cDirection
	{
		North,
		South,
		East,
		West,
		TypeCount
	};

	explicit			Entity(int hitpoints);

	void				setVelocity(sf::Vector2f velocity);
	void				setVelocity(float vx, float vy);
	void				accelerate(sf::Vector2f velocity);
	void				accelerate(float vx, float vy);
	void				guideTowards(sf::Vector2f position);
	sf::Vector2f		getVelocity() const;
	
	virtual int			getHitpoints() const;
	void				repair(int points);
	void				damage(int points);
	void				destroy();
	virtual bool		isDestroyed() const;
	bool				isImmune() const;
	void				setHitpoints(int points);
	virtual int			getMaxHitpoints() const;
	
protected:
	virtual void		updateCurrent(sf::Time dt, CommandQueue& commands);

private:
	void				checkImmunity(sf::Time dt);

private:
	sf::Vector2f		mVelocity;
	int					mHitpoints;
	int					mMaxHitpoints;
	bool				mImmunity;
	sf::Time			mImmunityCountdown;
	//cDirection			mCompass;
};

#endif // ENTITY_HPP