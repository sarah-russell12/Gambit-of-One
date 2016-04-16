/*
Category.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/

#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category
{
	enum Type
	{
		None = 0,
		SceneGroundLayer = 1 << 0,
		PlayerCreature = 1 << 1,
		AlliedCreature = 1 << 2,
		EnemyCreature = 1 << 3,
		Pickup = 1 << 4,
		AlliedProjectile = 1 << 5,
		EnemyProjectile = 1 << 6,
		InertScenery = 1 << 7,
		InteractiveScenery = 1 << 8,

		Creature = PlayerCreature | AlliedCreature | EnemyCreature,
		Projectile = AlliedProjectile | EnemyProjectile,
		Scenery = InertScenery | InteractiveScenery,
	};
}
#endif // CATEGORY_HPP