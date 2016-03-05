/*
Scenery.h

Date Last Updated: March 5, 2016

Scenery is a type of Entity that can block the path of Creatures and Projectiles.
*/

#pragma once

#ifndef SCENERY_H
#define SCENERY_H

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"


class Scenery : public Entity
{
public:
	enum Type
	{
		Rock,
		Tree1,
		Tree2,
		Fence,
		Wheat,
		House,
		TypeCount
	};


public:
	Scenery(Type type, const TextureHolder& textures);
	~Scenery();

	virtual unsigned int		getCategory() const;
	virtual sf::FloatRect		getBoundingRect() const;

private:
	virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void				updateCurrent(sf::Time dt, CommandQueue& commands);

private:
	sf::Texture		mTexture;
};

#endif //SCENERY_H

