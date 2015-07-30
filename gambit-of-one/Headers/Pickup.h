/*
Pickup.h

Sarah Russell

Date Last Updated: July 27, 2015

Pickups are another important part of gameplay in the genre of game we are
working with.  Without alterations or improvements to the player's stats, the
gameplay can be a very unsatisfying experience.  This is where pickups come
into play.  Pickups are entities that the player can obtain from enemy units
in order to alter their stats and, in effect, alter strategies.

Updates:
- July 27, 2015: Declared Pickup and defined its methods
*/

#ifndef PICKUP_H
#define PICKUP_H

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Command.hpp"
#include "Entity.h"
#include "Enumerations.hpp"
#include "ResourceHolder.hpp"

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

	virtual unsigned int	getCategory() const;
	virtual sf::FloatRect	getBoundingRect() const;

	void					apply(Creature& player) const;

protected:
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type					mType;
	sf::Sprite				mSprite;
};

#endif //PICKUP_H