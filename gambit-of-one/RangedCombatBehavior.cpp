/*
RangedCombatBehavior.cpp

Date Created: May 16, 2016

Defines all the methods declared in RangedCombatBehavior.h
*/

#include "Category.hpp"
#include "RangedCombatBehavior.h"
#include "Utility.hpp"

namespace
{
	const std::vector<CreatureData> Table = initializeCreatureData();
}

RangedCombatBehavior::RangedCombatBehavior(Creature::Type type, SceneNode& node, const TextureHolder& textures)
	: CombatBehavior(type, node)
{
	mAttackInterval = Table[type].attackInterval;
	mAttackCooldown = 3.f * Table[type].attackInterval;

	mFireCommand.category = Category::SceneGroundLayer;
	mFireCommand.action = [this, &textures](SceneNode& node, sf::Time)
	{
		createArrows(*mNode, textures);
	};
}

RangedCombatBehavior::~RangedCombatBehavior() {}

void RangedCombatBehavior::checkAttacks