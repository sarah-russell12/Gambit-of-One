#include "Headers/DataTables.hpp"
#include "Headers/Creature.hpp"


// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<CreatureData> initializeCreatureData()
{
	std::vector<CreatureData> data(Creature::TypeCount);

	data[Creature::Hero].hitpoints			= 100;
	data[Creature::Hero].speed				= 200.f;
	data[Creature::Hero].attackDamage		= 20;
	data[Creature::Hero].aggroDistance		= 0;
	data[Creature::Hero].fireInterval		= sf::seconds(1.f);
	data[Creature::Hero].attackInterval		= sf::seconds(1.f);
	data[Creature::Hero].normalTexture		= Textures::HeroFront;
	data[Creature::Hero].attackTexture		= Textures::HeroAttack;
	data[Creature::Hero].firingTexture		= Textures::HeroFire;

	// Rats run at the player, though they hit for little, they can be a real
	// pest if left to attack the player
	data[Creature::Rat].hitpoints			= 10;
	data[Creature::Rat].speed				= 200.f;
	data[Creature::Rat].attackDamage		= 5;
	data[Creature::Rat].aggroDistance		= 40;
	data[Creature::Rat].fireInterval		= sf::Time::Zero;
	data[Creature::Rat].attackInterval		= sf::seconds(2.f);
	data[Creature::Rat].normalTexture		= Textures::Rat;
	data[Creature::Rat].attackTexture		= Textures::RatAttack;
	data[Creature::Rat].firingTexture		= Textures::Rat;

	// Bandits move in a predetermined way and attack frequently
	data[Creature::Bandit].hitpoints		= 50;
	data[Creature::Bandit].speed			= 100.f;
	data[Creature::Bandit].attackDamage		= 10;
	data[Creature::Bandit].aggroDistance	= 0;
	data[Creature::Bandit].fireInterval		= sf::Time::Zero;
	data[Creature::Bandit].attackInterval	= sf::seconds(0.5f);
	data[Creature::Bandit].normalTexture	= Textures::Bandit;
	data[Creature::Bandit].attackTexture	= Textures::BanditAttack;
	data[Creature::Bandit].firingTexture	= Textures::Bandit;
	data[Creature::Bandit].directions.push_back(Direction(0.f, 50.f, +1.f));
	data[Creature::Bandit].directions.push_back(Direction(0.f, 50.f, -1.f));

	// Archers are stationary and fire arrows in one direction frequently
	data[Creature::Archer].hitpoints		= 25;
	data[Creature::Archer].speed			= 0.f;
	data[Creature::Archer].attackDamage		= 0;
	data[Creature::Archer].aggroDistance	= 0;
	data[Creature::Archer].fireInterval		= sf::seconds(0.5f);
	data[Creature::Archer].attackInterval	= sf::Time::Zero;
	data[Creature::Archer].normalTexture	= Textures::Archer;
	data[Creature::Archer].attackTexture	= Textures::Archer;
	data[Creature::Archer].firingTexture	= Textures::ArcherFire;

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

