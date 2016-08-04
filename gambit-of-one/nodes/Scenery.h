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
#include "DataStructures.h"

#include <SFML/Graphics/Sprite.hpp>


class Scenery : public Entity
{
public:
	enum Type
	{
		Rock,
		BigTree1,
		SmallTree1,
		TreeWallLong,
		TreeWallLeftCorner,
		TreeWallRightCorner,
		Fence,
		Wheat,
		House,
		TypeCount
	};


public:
	Scenery(Type type, const TextureHolder& textures, const SceneryData& data);
	~Scenery();

	virtual unsigned int		getCategory() const;
	virtual sf::FloatRect		getBoundingRect() const;

	Type						getType() const;

private:
	virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type			mType;
	sf::Sprite		mSprite;
};

struct ScenerySpawn
{
	ScenerySpawn(Scenery::Type type, float x, float y)
		: type(type), x(x), y(y) {}
	ScenerySpawn(Scenery::Type type, sf::Vector2f pos)
		: type(type), x(pos.x), y(pos.y) {}

	Scenery::Type	type;
	float			x;
	float			y;
};

#endif //SCENERY_H

