/*
Pickup.h

Date Last Updated: June 21, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use most of "facilities" header files anymore
*/

#ifndef PICKUP_H
#define PICKUP_H

#include "Entity.h"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "SFML_facilities.h"
#include "UtilityFunctions.hpp"

#include <vector>

class Creature;

class Pickup : public Entity
{
public:
	enum Type
	{
		HealthRefill,
		ArrowRefill,
		TypeCount,
	};

public:
	Pickup(Type type, const TextureHolder& textures);

	virtual unsigned int		getCategory() const;
	virtual sf::FloatRect		getBoundingRect() const;

	void						apply(Creature& player) const;

protected:
	virtual void		drawCurrent(sf::RenderTarget& target,
						sf::RenderStates states) const;

private:
	Type				mType;
	sf::Sprite			mSprite;
};

#endif //PICKUP_H