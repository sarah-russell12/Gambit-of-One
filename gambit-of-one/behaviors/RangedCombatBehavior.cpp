/*
RangedCombatBehavior.cpp

Date Created: May 16, 2016

Defines all the methods declared in RangedCombatBehavior.h
*/

#include "..\Category.hpp"
#include "..\nodes\Entity.hpp"
#include "RangedCombatBehavior.h"
#include "..\Utility.hpp"

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
		createArrow(*mNode, textures);
	};
}

RangedCombatBehavior::~RangedCombatBehavior() {}

void RangedCombatBehavior::checkAttacks(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos)
{
	if (mIsAttacking)
	{
		mAttackInterval -= dt;
		if (mAttackInterval <= sf::Time::Zero)
		{
			mIsAttacking = false;
			mAttackInterval = Table[mType].attackInterval;
		}
		mAttackCooldown -= dt;
	}
	else
	{
		mAttackCooldown -= dt;
		if (mAttackCooldown <= sf::Time::Zero)
		{
			attack(commands);
			mAttackCooldown = 3.f * Table[mType].attackInterval;
		}
	}
}

void RangedCombatBehavior::attack(CommandQueue& commands)
{
	// No range check required
	commands.push(mFireCommand);
}

void RangedCombatBehavior::createArrow(SceneNode& node, const TextureHolder& textures) const
{
	auto& creature = static_cast<Creature&>(node);
	Projectile::Type type = creature.isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;
	std::unique_ptr<Projectile> projectile(new Projectile(type, textures, creature.getCompass()));

	sf::Vector2f velocity;
	switch (creature.getCompass())
	{
	case Creature::cDirection::North:
		velocity.x = 0;
		velocity.y = projectile->getMaxSpeed() * -1.f;
		break;
	case Creature::cDirection::South:
		velocity.x = 0;
		velocity.y = projectile->getMaxSpeed();
		break;
	case Creature::cDirection::East:
		velocity.x = projectile->getMaxSpeed();
		velocity.y = 0;
		break;
	case Creature::cDirection::West:
		velocity.x = projectile->getMaxSpeed() * -1.f;
		velocity.y = 0;
		break;
	}

	projectile->setPosition(creature.getWorldPosition());
	projectile->setVelocity(velocity);
	node.attachChild(std::move(projectile));
}