#include "DataTables.hpp"


// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<CreatureData> initializeCreatureData()
{
	std::vector<CreatureData> data(Creature::TypeCount);

	data[Creature::Rat].hitpoints = 100;
	data[Creature::Rat].speed = 100;
	data[Creature::Rat].damage = 5;
	//aggrodistance-> distance from player at which an idle enemy becomes aggressive
	//data[Creature::Rat].aggrodistance = tba;
	data[Creature::Rat].texture = Textures::Rat;


	/*data[Aircraft::Eagle].hitpoints = 100;
	data[Aircraft::Eagle].speed = 200.f;
	data[Aircraft::Eagle].fireInterval = sf::seconds(1);
	data[Aircraft::Eagle].texture = Textures::Eagle;

	data[Aircraft::Raptor].hitpoints = 20;
	data[Aircraft::Raptor].speed = 80.f;
	data[Aircraft::Raptor].texture = Textures::Raptor;
	data[Aircraft::Raptor].directions.push_back(Direction(+45.f, 80.f));
	data[Aircraft::Raptor].directions.push_back(Direction(-45.f, 160.f));
	data[Aircraft::Raptor].directions.push_back(Direction(+45.f, 80.f));
	data[Aircraft::Raptor].fireInterval = sf::Time::Zero;

	data[Aircraft::Avenger].hitpoints = 40;
	data[Aircraft::Avenger].speed = 50.f;
	data[Aircraft::Avenger].texture = Textures::Avenger;
	data[Aircraft::Avenger].directions.push_back(Direction(+45.f, 50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(0.f, 50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(-45.f, 100.f));
	data[Aircraft::Avenger].directions.push_back(Direction(0.f, 50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(+45.f, 50.f));
	data[Aircraft::Avenger].fireInterval = sf::seconds(2);*/

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

	data[Pickup::HealthRefill].texture = Textures::HealthRefill;
	data[Pickup::HealthRefill].action = [](Creature& a) { a.repair(25); };

	data[Pickup::ArrowRefill].texture = Textures::Quiver;
	data[Pickup::ArrowRefill].action = std::bind(&Creature::collectArrows, _1, 3);



	return data;
}