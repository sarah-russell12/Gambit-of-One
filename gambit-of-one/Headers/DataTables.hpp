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

#include "Projectile.h"
#include "Creature.hpp"
#include "Enumerations.hpp"
#include "Pickup.h"
#include "SFML_facilities.h"

#include <vector>
#include <functional>


class Creature;

struct Direction
{
	Direction(float angle, float distance, float sign)
		: angle(angle), distance(distance), sign(sign){}

	float			angle;
	float			distance;
	float			sign;
};

struct CreatureData
{
	// hitpoints:		how much damage the Creature can take before it is dead
	// speed:			the speed the creature travels across the screen, in
	//					in pixels(?)
	// attackDamage:	If a creature can physically attack, then it will have
	//					a physical attack damage
	// aggroDistance:	aggro is a gaming term short for "aggrovation". It is
	//					the state of an attackable entity that means they are
	//					actively trying to kill the player.  Aggro distance is
	//					how close the player has to be to have the creature
	//					aggro them
	// fireInterval:	ranged attackers fire arrows periodically
	// attackInterval:	melee attackers attack periodically
	// directions:		some creatures move in set paths, the directions define
	//					them
	int								hitpoints;
	float							speed;
	int								attackDamage;
	float							aggroDistance;
	Textures::ID					normalTexture;
	Textures::ID					attackTexture;
	Textures::ID					firingTexture;
	sf::Time						fireInterval;
	sf::Time						attackInterval;
	std::vector<Direction>			directions;
};



struct PickupData
{
	std::function<void(Creature&)>	action;
	Textures::ID					texture;
};

struct ProjectileData
{
	int                                damage;
	float                            speed;
	Textures::ID                    texture;
};

std::vector<CreatureData>	initializeCreatureData();
std::vector<ProjectileData>	initializeProjectileData();
std::vector<PickupData>		initializePickupData();

#endif // DATATABLES_HPP