/*
Pickup.hpp

Date Last Updated: August 2, 2016

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Pickups are another important part of gameplay in the genre of game we are
working with.  Without alterations or improvements to the player's stats, the
gameplay can be a very unsatisfying experience.  This is where pickups come
into play.  Pickups are entities that the player can obtain from enemy units
in order to alter their stats and, in effect, alter strategies.  They also can
restore the player's health so they can continue playing.

Updates:
	- August 2, 2016: Has a PickupData as a member
*/

#ifndef PICKUP_HPP
#define PICKUP_HPP

#include "Entity.hpp"
#include "Command.hpp"
#include "ResourceIdentifiers.hpp"
#include "DataStructures.h"

#include <SFML/Graphics/Sprite.hpp>


class Creature;

class Pickup : public Entity
{
public:
	enum Type
	{
		HealthRefill,
		FireSpread,
		FireRate,
		TypeCount
	};


public:
	Pickup(Type type, const TextureHolder& textures, const PickupData& data);

	virtual unsigned int	getCategory() const;
	virtual sf::FloatRect	getBoundingRect() const;

	void 					apply(Creature& player) const;


protected:
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	Type 					mType;
	sf::Sprite				mSprite;
	PickupData				mData;
};

#endif // PICKUP_HPP