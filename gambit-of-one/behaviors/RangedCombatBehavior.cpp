/*
RangedCombatBehavior.cpp

Date Created: May 16, 2016

Date Last Updated: July 4, 2016

Defines all the methods declared in RangedCombatBehavior.h
*/

#include "Category.hpp"
#include "RangedCombatBehavior.h"
#include "ResourceIdentifiers.hpp"
#include "Utility.hpp"

namespace
{
	const std::vector<CreatureData> Table = initializeCreatureData();
}

RangedCombatBehavior::RangedCombatBehavior(Creature& node)
	: CombatBehavior(node), mIsFiring(false)
{
	mAttackInterval = sf::Time::Zero;
	mAttackCooldown = 3.f * Table[mType].attackInterval;
}

RangedCombatBehavior::~RangedCombatBehavior() {}

void RangedCombatBehavior::updateCombatPattern(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos)
{
	checkCooldown(dt, playerPos);
	checkInterval(dt, commands);
}

void RangedCombatBehavior::checkCooldown(sf::Time dt, sf::Vector2f playerPos)
{
	// 1: Decriment cooldown interval
	mAttackCooldown -= dt;

	// 2: Check that the attack interval is not currently going on. If that is the case, return, since
	//    the Creature should still be in their attack posture
	if (mAttackInterval >= sf::Time::Zero)
	{
		mIsAttacking = true;
		return;
	}

	// 2: Check for Player asking for an attack when the attack is on cooldown and not being performed
	//	  If so, set mIsAttacking to false and return
	if (mIsAttacking && mAttackCooldown >= sf::Time::Zero)
	{
		mIsAttacking = false;
		return;
	}

	// 3: Check if the cooldown has hit zero.  If so, handle attack conditions, reset cooldown,
	//	  start the attack interval, and return
	if (mAttackCooldown <= sf::Time::Zero)
	{
		// If it is not an allied creature, it will auto attack, else the player has requested
		// PlayerCreature attacks
		if (!mCreature->isAllied() || mIsAttacking)
		{
			mIsFiring = true;
			mIsAttacking = true;
			mAttackInterval = Table[mType].attackInterval;
			mAttackCooldown = 3.f * mAttackInterval;
			return;
		}
	}
}

void RangedCombatBehavior::attack()
{
	mIsAttacking = true;
}

void RangedCombatBehavior::checkInterval(sf::Time dt, CommandQueue& commands)
{
	// Handling the attack interval is only necessary when the Creature is
	// attacking
	if (!mIsAttacking) return;
	
	// Simple check for firing an arrow at the start of the attack interval
	if (mIsFiring)
	{
		mCreature->fire(commands);
		mIsFiring = false;
	}

	mAttackInterval -= dt;

	// The Creature will maintain an attack stance for a time
	if (mAttackInterval <= sf::Time::Zero)
	{
		mIsAttacking = false;
	}
}

void RangedCombatBehavior::attack(CommandQueue& commands)
{
	// No range check required
	
}