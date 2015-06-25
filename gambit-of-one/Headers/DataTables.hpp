/*
DataTables.hpp

Date Last Updated: June 20, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use "facilities" header files anymore
*/

#ifndef DATATABLES_HPP
#define DATATABLES_HPP


#include "Creature.hpp"
#include "Enumerations.hpp"
#include "Pickup.h"
#include "Projectile.h"
#include "SFML_facilities.h"

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