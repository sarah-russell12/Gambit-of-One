/*
DataTable.h

Date Created: August 1, 2016

Date Last Updated: August 1, 2016

This class moves all the data loading for the entities, areas, and resources
into one place.

This class uses the pugixml library (http://pugixml.org) to parse xml documents.
pugixml is Copyright (C) 2006-2015 Arseny Kapoulkine.
*/

#pragma once
#ifndef DATA_TABLE_H
#define DATA_TABLE_H

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

class DataTable
{
public:
	DataTable();
	~DataTable();

public:
	void										initializeData();

	std::vector<CreatureData>					getCreatureData() const;
	std::vector<ProjectileData>					getProjectileData() const;
	std::vector<PickupData>						getPickupData() const;
	std::vector<SceneryData>					getSceneryData() const;
	std::vector<std::vector<AreaData>>			getAreaData() const;

	TextureHolder								getTextures() const;
	FontHolder									getFonts() const;

private:
	void										initializeCreatureData();
	void										initializeProjectileData();
	void										initializePickupData();
	void										initializeSceneryData();
	void										initializeAreaData();

	void										loadResources();

private:
	std::vector<CreatureData>					mCreatureData;
	std::vector<ProjectileData>					mProjectileData;
	std::vector<PickupData>						mPickupData;
	std::vector<SceneryData>					mSceneryData;
	std::vector<std::vector<AreaData>>			mAreaData;

	TextureHolder								mTextures;
	FontHolder									mFonts;
};

#endif DATA_TABLE_H