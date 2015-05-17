/*
	Enumerations.hpp

	Author: Sarah Russell
	Last Updated: 16 April, 2015

	A collection of enumerations.
*/

#ifndef ENUMERATIONS_HPP
#define ENUMERATIONS_HPP

namespace Textures
{
	enum ID
	{
		HeroFront,
		Rat,
		Thief,
		Archer,
		Arrow,
		HealthPotion,
		Quiver,
		WoodHouse,
		DirtRoad,
		TitleScreen,
		BigButtonNormal,
		BigButtonSelected,
		BigButtonPressed,
		SmallButtonNormal,
		SmallButtonSelected,
		SmallButtonPressed
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