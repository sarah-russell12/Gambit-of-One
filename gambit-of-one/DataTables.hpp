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


std::vector<CreatureData>	initializeCreatureData();
std::vector<ProjectileData>	initializeProjectileData();
std::vector<PickupData>		initializePickupData();

#endif // DATATABLES_HPP