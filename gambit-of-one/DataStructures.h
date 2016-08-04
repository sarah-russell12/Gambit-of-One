/*
DataStructures.h

Date Created: August 2, 2016

Date Last Updated: August 2, 2016

This file is a holder for all the -Data structs that the game uses to represent
the stats of entities and areas.  It made sense in the original implementation
to keep these along with the global functions that created their data tables.
Now that it is being relegated to a class, this reduces the clutter.
*/


#pragma once
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "ResourceIdentifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <map>
#include <vector>
#include <functional>

class Creature;
struct EnemySpawn;

class Scenery;
struct ScenerySpawn;

struct Direction
{
	Direction(float angle, float distance, float sign)
		: angle(angle)
		, distance(distance)
		, sign(sign)
	{
	}

	float angle;
	float distance;
	float sign;
};

struct TeleportPoint
{
	TeleportPoint(float x, float y, Compass comp)
		: pos(x, y), compass(comp) {}
	sf::Vector2f pos;
	Compass compass;
};

struct CreatureData
{
	int								hitpoints;
	float							speed;
	int								attackDamage;
	float							aggroDistance;
	Textures::ID					texture;
	sf::IntRect						textureRect;
	sf::Time						attackInterval;
	std::vector<Direction>			directions;
	std::vector<TeleportPoint>		teleportPoints;
};

struct ProjectileData
{
	int								damage;
	float							speed;
	Textures::ID					texture;
};

struct PickupData
{
	std::function<void(Creature&)>	action;
	Textures::ID					texture;
};

struct SceneryData
{
	Textures::ID					texture;
};

struct InteractiveSceneryData
{
	Textures::ID					texture;
	sf::IntRect						textureRect;
	bool							isSwitch;
	bool							isMoveable;
};

struct AreaData
{
	// coordinates: relative to the entirety of the map, not the drawing space
	// bgTexture: The large texture that the area uses
	// enemySpawns: The enemies in the area
	// scenerySpawns: The scenery in the area, some of which is useful for 
	//                blocking the path to non-existant areas
	sf::Vector2i				coordinates;
	Textures::ID				bgTexture;
	std::vector<EnemySpawn>		enemySpawns;
	std::vector<ScenerySpawn>	scenerySpawns;
};

#endif // DATA_STRUCTURES_H