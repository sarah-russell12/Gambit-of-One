/*
Projectile.h

Date Last Updated: June 21, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use most of "facilities" header files anymore
- June 25, 2015:
	- Implemented methods that were not implemented previously
*/

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "CommandQueue.h"
#include "DataTables.hpp"
#include "Entity.h"
#include "ResourceHolder.hpp"
#include "SFML_facilities.h"
#include "UtilityFunctions.hpp"

#include <cmath>
#include <assert.h>
#include <vector>

struct ProjectileData;

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

	void			guideTowards(sf::Vector2f position);
	bool			isGuided() const;

	virtual unsigned int		getCategory() const;
	virtual sf::FloatRect		getBoundingRect() const;
	float						getMaxSpeed() const;
	int							getDamage() const;

private:
	virtual void				updateCurrent(sf::Time dt, 
									CommandQueue& commands);
	virtual void				drawCurrent(sf::RenderTarget& target,
									sf::RenderStates states) const;

private:
	Type						mType;
	sf::Sprite					mSprite;
	sf::Vector2f				mTargetDirection;
};

#endif //PROJECTILE_H