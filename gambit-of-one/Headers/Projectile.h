/*
Projectile.h

Sarah Russell

Date Last Updated: July 26, 2015

Pojectiles are key Entities in the implementation of this game's mechanics.
Since this game is a jet pilot shoot-em-up, the projectiles are the shooting
implements and are essential for combat.

Updates:
- July 26, 2015: Declared Projectile
*/

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <cassert>

#include "CommandQueue.h"
#include "Entity.h"
#include "Enumerations.hpp"
#include "ResourceHolder.hpp"

class Projectile : public Entity
{
public:
	enum Type
	{
		AlliedArrow,
		EnemyArrow,
		TypeCount,
	};

public:
						Projectile(Type type, const TextureHolder& textures);

	void				guideTowards(sf::Vector2f position);
	bool				isGuided() const;

	virtual unsigned int		getCategory() const;
	virtual sf::FloatRect		getBoundingRect() const;
	float						getMaxSpeed() const;
	int							getDamage() const;

private:
	virtual void		updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type				mType;
	sf::Sprite			mSprite;
	sf::Vector2f		mTargetDirection;
};

#endif //PROJECTILE_H