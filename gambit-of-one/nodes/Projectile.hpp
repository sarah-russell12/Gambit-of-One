/*
Projectile.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Projectiles are Entities that aid in combat.  They are shot both by
enemies and the player and are meant to inflict damage to those that
interact with them.
*/

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Projectile : public Entity
{
public:
	enum Type
	{
		AlliedBullet,
		EnemyBullet,
		Magic,
		TypeCount
	};


public:
	Projectile(Type type, const TextureHolder& textures, const Compass& direction);

	void					guideTowards(sf::Vector2f position);
	bool					isGuided() const;

	virtual unsigned int	getCategory() const;
	virtual sf::FloatRect	getBoundingRect() const;
	float					getMaxSpeed() const;
	int						getDamage() const;
	void					updateSprite();

	void					setStats(unsigned int main, unsigned int limiter);

	//void					setSprite();

private:
	virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	Type									mType;
	sf::Sprite								mSprite;
	sf::Sprite								OriginSprite;
	sf::Vector2f							mTargetDirection;
	Compass									mCDirection;

	// Projectile damage is based on the main stat and limiting stat of the
	// Creature making it
	unsigned int							mMain;
	unsigned int							mLimiter;
};

#endif // PROJECTILE_HPP