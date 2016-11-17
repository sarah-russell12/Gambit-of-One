/*
MeleeCombatBehavior.cpp

Date Created: May 16, 2016

Defines all the functions declared in MeleeCombatBehavior.h
*/

#include "MeleeCombatBehavior.h"
#include "Utility.hpp"

using namespace Tables;

MeleeCombatBehavior::MeleeCombatBehavior(Creature& node)
	: CombatBehavior(node)
{
	setStats();
	mAttackInterval = sf::Time::Zero;
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
		setAction(Player::Attack);
		return;
	}

	// 2: Check for Player asking for an attack when the attack is on cooldown and not being performed
	//	  If so, set mIsAttacking to false and return
	if (mIsAttacking && mAttackCooldown >= sf::Time::Zero)
	{
		mIsAttacking = false;
		setAction(Player::ActionCount);
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
			setStats();
			return;
		}
		if (mIsAttacking)
		{
			// The player
			setStats();
			return;
		}
	}
}

void MeleeCombatBehavior::attack()
{
	mIsAttacking = true;
	setAction(Player::Attack);
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
		setAction(Player::ActionCount);
	}
}

void MeleeCombatBehavior::attack(sf::Vector2f playerPos)
{
	// a percieved enemy needs to be REALLY up close and personal with the creature
	// for it to attack

	float distance = length(mCreature->getPosition() - playerPos);
	if (distance <= (Creatures[mCreature->getID()].aggroDistance / 10.f))
	{
		mIsAttacking = true;
	}
}

void MeleeCombatBehavior::setStats()
{
	CreatureData stats = mCreature->getData();
	float time = (stats.strength * 0.25f) + (stats.dexterity * 0.125f);
	mAttackInterval = sf::seconds(time);
	float offtime;
	setAction(Player::ActionCount);
	if (stats.strength < 5) {
		// poor strength means longer time
		offtime = (5 - stats.strength) * 2.f;
	}
	else {
		offtime = 2.f;
	}
	if (stats.dexterity >= (stats.strength / 2.f)) {
		// if you are good with your hands, then you can attack a bit sooner
		offtime -= stats.dexterity * 0.125f;
	}
	mAttackCooldown = mAttackInterval + sf::seconds(offtime);
}