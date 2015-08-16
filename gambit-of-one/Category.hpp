#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category
{
	enum Type
	{
		None = 0,
		SceneAirLayer = 1 << 0,
		PlayerCreature = 1 << 1,
		AlliedCreature = 1 << 2,
		EnemyCreature = 1 << 3,
		Pickup = 1 << 4,
		AlliedProjectile = 1 << 5,
		EnemyProjectile = 1 << 6,

		Aircraft = PlayerCreature | AlliedCreature | EnemyCreature,
		Projectile = AlliedProjectile | EnemyProjectile,
	};
}
#endif // CATEGORY_HPP