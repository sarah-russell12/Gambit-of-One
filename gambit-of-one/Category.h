#ifndef CATEGORY_H
#define CATEGORY_H

namespace Category
{
	enum Type
	{
		None = 0,
		Scene = 1 << 0,
		Player = 1 << 1,
		NPCHumanoid = 1 << 2,
		EnemyHumanoid = 1 << 3,
		NPCAnimal = 1 << 4,
		EnemyAnimal = 1 << 5,
	};
};


#endif //CATEGORY_H