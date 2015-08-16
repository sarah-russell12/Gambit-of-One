/*
DataTables.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/

#include "DataTables.hpp"
#include "Creature.hpp"
#include "Projectile.hpp"
#include "Pickup.hpp"


// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<CreatureData> initializeCreatureData()
{
	std::vector<CreatureData> data(Creature::TypeCount);

	data[Creature::Hero].hitpoints = 100;
	data[Creature::Hero].speed = 200.f;
	data[Creature::Hero].attackDamage = 20;
	data[Creature::Hero].aggroDistance = 0;
	data[Creature::Hero].attackInterval = sf::seconds(0.5f);
	data[Creature::Hero].fireInterval = sf::seconds(1);
	data[Creature::Hero].texture = Textures::Hero;
	data[Creature::Hero].textureRect = sf::IntRect(0, 0, 62, 66);
	
	// Rats run at the player, though they hit for little, they can be a real
	// pest if left to attack the player
	data[Creature::Rat].hitpoints = 50;
	data[Creature::Rat].speed = 50.f;
	data[Creature::Rat].attackDamage = 5;
	data[Creature::Rat].aggroDistance = 300.f;
	data[Creature::Rat].fireInterval = sf::Time::Zero;
	data[Creature::Rat].attackInterval = sf::seconds(2.f);
	data[Creature::Rat].texture = Textures::Rat;
	data[Creature::Rat].textureRect = sf::IntRect(0, 0, 34, 16);
	
	// Bandits move in a predetermined way and attack frequently
	data[Creature::Bandit].hitpoints = 80;
	data[Creature::Bandit].speed = 100.f;
	data[Creature::Bandit].attackDamage = 10;
	data[Creature::Bandit].aggroDistance = 200.f;
	data[Creature::Bandit].fireInterval = sf::Time::Zero;
	data[Creature::Bandit].attackInterval = sf::seconds(0.5f);
	data[Creature::Bandit].texture = Textures::Bandit;
	data[Creature::Bandit].textureRect = sf::IntRect(0, 0, 48, 67);


	// Archers are stationary and fire arrows in one direction frequently
	data[Creature::Archer].hitpoints = 60;
	data[Creature::Archer].speed = 0.f;
	data[Creature::Archer].attackDamage = 0;
	data[Creature::Archer].aggroDistance = 500.f;
	data[Creature::Archer].fireInterval = sf::seconds(3.f);
	data[Creature::Archer].attackInterval = sf::Time::Zero;
	data[Creature::Archer].texture = Textures::Archer;
	data[Creature::Archer].textureRect = sf::IntRect(0, 0, 35, 59);


	return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
	std::vector<ProjectileData> data(Projectile::TypeCount);

	data[Projectile::AlliedBullet].damage = 10;
	data[Projectile::AlliedBullet].speed = 300.f;
	data[Projectile::AlliedBullet].texture = Textures::Arrow;

	data[Projectile::EnemyBullet].damage = 10;
	data[Projectile::EnemyBullet].speed = 300.f;
	data[Projectile::EnemyBullet].texture = Textures::Arrow;

	return data;
}

std::vector<PickupData> initializePickupData()
{
	std::vector<PickupData> data(Pickup::TypeCount);

	data[Pickup::HealthRefill].texture = Textures::HealthRefill;
	data[Pickup::HealthRefill].action = [](Creature& a) { a.repair(25); };

	data[Pickup::MissileRefill].texture = Textures::MissileRefill;

	data[Pickup::FireSpread].texture = Textures::FireSpread;
	data[Pickup::FireSpread].action = std::bind(&Creature::increaseSpread, _1);

	data[Pickup::FireRate].texture = Textures::FireRate;
	data[Pickup::FireRate].action = std::bind(&Creature::increaseFireRate, _1);

	return data;
}