/*
DataTables.hpp

Date Last Updated: August 4, 2016

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

In gameplay there are many stats that need to be accounted for, since even one
subclass of Entities can have different types, which means different stats.  We
need all this data to be organized in one place so that we can just grab it
when we need it and not have to worry about consistency or unnecessary logic
blocks messing with the readability of our code.

These methods use the pugixml library (http://pugixml.org) to parse xml documents.
pugixml is Copyright (C) 2006-2015 Arseny Kapoulkine.

Updates:
	- July 4, 2016: Updated CreatureData to remove redundant stats.  Added 
					three new structs: EnemySpawn, ScenerySpawn, and
					AreaData. New global function InitializeAreaData()
	- August 4, 2016: Updated global methods to implement the pugixml library
					  to parse xml files
*/

#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include "ResourceIdentifiers.hpp"
#include "Scenery.h"
#include "Creature.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <map>
#include <vector>
#include <functional>

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

struct EnemySpawn
{
	EnemySpawn(Creature::Type type, float x, float y)
		: type(type), x(x), y(y) {}
	EnemySpawn(Creature::Type type, sf::Vector2f pos)
		: type(type), x(pos.x), y(pos.y) {}

	Creature::Type	type;
	float			x;
	float			y;
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

std::vector<CreatureData>				initializeCreatureData();
std::vector<ProjectileData>				initializeProjectileData();
std::vector<PickupData>					initializePickupData();
std::vector<SceneryData>				initializeSceneryData();
std::vector<InteractiveSceneryData>		initializeInteractiveSceneryData();
std::vector<std::vector<AreaData>>		initializeAreaData();

#endif // DATATABLES_HPP