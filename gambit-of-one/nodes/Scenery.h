/*
Scenery.h

Date Last Updated: March 5, 2016

Scenery is a type of Entity that can block the path of Creatures and Projectiles.
*/

#pragma once

#ifndef SCENERY_H
#define SCENERY_H

#include "Entity.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Scenery : public Entity
{
public:
	Scenery(unsigned int type, const TextureHolder& textures);
	~Scenery();

	virtual unsigned int		getCategory() const;
	virtual sf::FloatRect		getBoundingRect() const;

	unsigned int				getType() const;

private:
	virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	unsigned int				mType;
	sf::Sprite					mSprite;
};

#endif //SCENERY_H

