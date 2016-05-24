/*
MeleeCombatBehavior.cpp

Date Created: May 16, 2016

Defines all the functions declared in MeleeCombatBehavior.h
*/

#include "MeleeCombatBehavior.h"
#include "..\Utility.hpp"

namespace
{
	const std::vector<CreatureData> Table = initializeCreatureData();
}

MeleeCombatBehavior::MeleeCombatBehavior(Creature::Type type, SceneNode& node)
	: CombatBehavior(type, node)
{
	mAttackInterval = Table[type].attackInterval;
	mAttackCooldown = 2.f * Table[type].attackInterval;
}

MeleeCombatBehavior::~MeleeCombatBehavior() {}

void MeleeCombatBehavior::checkAttacks(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos)
{
	if (mIsAttacking)
	{
		// the creature is attacking, hold that for the interval
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
		// the creature is not attacking, prepare to attack when the cooldown ends
		mAttackCooldown -= dt;
		if (mAttackCooldown <= sf::Time::Zero)
		{
			attack(playerPos);
			mAttackCooldown = 2.f * Table[mType].attackInterval;
		}
	}
}

void MeleeCombatBehavior::attack(sf::Vector2f playerPos)
{
	// a percieved enemy needs to be REALLY up close and personal with the creature
	// for it to attack

	float distance = length(mNode->getPosition() - playerPos);
	if (distance <= (Table[mType].aggroDistance / 10.f))
	{
		mIsAttacking = true;
	}
}