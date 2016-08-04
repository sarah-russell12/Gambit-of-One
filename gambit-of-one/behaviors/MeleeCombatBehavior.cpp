/*
MeleeCombatBehavior.cpp

Date Created: May 16, 2016

Defines all the functions declared in MeleeCombatBehavior.h
*/

#include "MeleeCombatBehavior.h"
#include "Utility.hpp"

MeleeCombatBehavior::MeleeCombatBehavior(Creature& node, const CreatureData& data)
	: CombatBehavior(node, data)
{
	mAttackInterval = sf::Time::Zero;
	mAttackCooldown = 2.f * mData.attackInterval;
}

MeleeCombatBehavior::~MeleeCombatBehavior() {}

void MeleeCombatBehavior::updateCombatPattern(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos)
{
	checkCooldown(dt, playerPos);
	checkInterval(dt, commands);
}

void MeleeCombatBehavior::checkCooldown(sf::Time dt, sf::Vector2f playerPos)
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
	//	  start the attack interval, and return.
	if (mAttackCooldown <= sf::Time::Zero)
	{
		if (!mCreature->isAllied())
		{
			// Auto-attacking enemy
			attack(playerPos);
			mAttackInterval = mData.attackInterval;
			mAttackCooldown = 2.f * mAttackInterval;
			return;
		}
		if (mIsAttacking)
		{
			// The player
			mAttackInterval = mData.attackInterval;
			mAttackCooldown = 2.f * mAttackInterval;
			return;
		}
	}
}

void MeleeCombatBehavior::attack()
{
	mIsAttacking = true;
}

void MeleeCombatBehavior::checkInterval(sf::Time dt, CommandQueue& commands)
{
	// Handling the attack interval is only necessary when the Creature is
	// attacking
	if (!mIsAttacking) return;

	mAttackInterval -= dt;
	
	if (mAttackInterval <= sf::Time::Zero)
	{
		mIsAttacking = false;
	}
}

void MeleeCombatBehavior::attack(sf::Vector2f playerPos)
{
	// a percieved enemy needs to be REALLY up close and personal with the creature
	// for it to attack

	float distance = length(mCreature->getPosition() - playerPos);
	if (distance <= (mData.aggroDistance / 10.f))
	{
		mIsAttacking = true;
	}
}