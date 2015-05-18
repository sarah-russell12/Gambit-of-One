#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include "SFML_facilities.h"
#include "Enumerations.hpp"
#include "Entities_Facilities.h"

#include <vector>
#include <functional>


class Creature;

struct Direction
{
	Direction(float angle, float distance)
		: angle(angle)
		, distance(distance)
	{
	}

	float angle;
	float distance;
};

struct CreatureData
{
	int								hitpoints;
	float							speed;
	int								damage;
	Textures::ID					texture;
	sf::Time						fireInterval;
	std::vector<Direction>			directions;
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


std::vector<CreatureData>	initializeAircraftData();
std::vector<ProjectileData>	initializeProjectileData();
std::vector<PickupData>		initializePickupData();

#endif // DATATABLES_HPP