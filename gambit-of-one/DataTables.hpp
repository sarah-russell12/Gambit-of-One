/*
DataTables.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

In gameplay there are many stats that need to be accounted for, since even one
subclass of Entities can have different types, which means different stats.  We
need all this data to be organized in one place so that we can just grab it
when we need it and not have to worry about consistency or unnecessary logic
blocks messing with the readability of our code.
*/

#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include "ResourceIdentifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>


class Creature;

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
	Textures::ID					attackTexture;
	Textures::ID					firingTexture;
	sf::Time						fireInterval;
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

std::vector<CreatureData>				initializeCreatureData();
std::vector<ProjectileData>				initializeProjectileData();
std::vector<PickupData>					initializePickupData();
std::vector<SceneryData>				initializeSceneryData();
std::vector<InteractiveSceneryData>		initializeInteractiveSceneryData();

#endif // DATATABLES_HPP