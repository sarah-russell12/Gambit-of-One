/*
Enumerations.hpp

Date Last Updated: June 20, 2015

A collection of enumerations

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use "facilities" header files anymore
*/

#ifndef ENUMERATIONS_HPP
#define ENUMERATIONS_HPP

namespace Textures
{
	enum ID
	{
		HeroFront,
		HeroAttack,
		HeroFire,
		Rat,
		RatAttack,
		Bandit,
		BanditAttack,
		Archer,
		ArcherFire,
		Arrow,
		HealthPotion,
		Quiver,
		WoodHouse,
		DirtRoad,
		TitleScreen,
		ButtonNormal,
		ButtonSelected,
		ButtonPressed,
	};
};

namespace Fonts
{
	enum ID
	{
		Main,
	};
};

namespace States
{
	enum ID
	{
		Game,
		Title,
		Menu,
		Pause,
		Settings,
		GameOver,
	};
};

namespace Category
{
	enum Type
	{
		None = 0,
		Scene = 1 << 0,
		Player = 1 << 1,
		Enemy = 1 << 2,
		Pickup = 1 << 3,
		AlliedProjectile = 1 << 4,
		EnemyProjectile = 1 << 5,

		Creature = Player | Enemy,
		Projectile = AlliedProjectile | EnemyProjectile,
	};
};

#endif //ENUMERATIONS_HPP