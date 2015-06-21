#include "Headers/DataTables.hpp"


// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<CreatureData> initializeCreatureData()
{
	std::vector<CreatureData> data(Creature::TypeCount);

	// Rat is a melee damaging creature that will converge on the player
	// Also, they are very, very weak
	data[Creature::Rat].hitpoints = 20;
	data[Creature::Rat].speed = 100.f;
	data[Creature::Rat].damage = 5;
	//aggrodistance-> distance from player at which an idle enemy becomes aggressive
	//data[Creature::Rat].aggrodistance = tba;
	data[Creature::Rat].texture = Textures::Rat;

	// Archers are stationary enemies that fire arrows
	// Harder to get rid of than rats, but arrows are avoidable
	//data[Creature::Archer].hitpoints = 40;
	//data[Creature::Archer].speed = 0.f;
	// Archers will still slap the player if they get close
	//data[Creature::Archer].damage = 5;
	return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
	std::vector<ProjectileData> data(Projectile::TypeCount);

	data[Projectile::AlliedArrow].damage = 10;
	data[Projectile::AlliedArrow].speed = 300.f;
	data[Projectile::AlliedArrow].texture = Textures::Arrow;

	data[Projectile::EnemyArrow].damage = 10;
	data[Projectile::EnemyArrow].speed = 300.f;
	data[Projectile::EnemyArrow].texture = Textures::Arrow;


	return data;
}

std::vector<PickupData> initializePickupData()
{
	std::vector<PickupData> data(Pickup::TypeCount);

	data[Pickup::HealthRefill].texture = Textures::HealthPotion;
	data[Pickup::HealthRefill].action = [](Creature& a) { a.repair(25); };

	data[Pickup::ArrowRefill].texture = Textures::Quiver;
	data[Pickup::ArrowRefill].action = std::bind(&Creature::collectArrows, _1, 3);



	return data;
}