/*
CombatBehavior.cpp

Date Created: May 16, 2016

Defines the non pure virtual functions declared in CombatBehavior.h
*/

#include "CombatBehavior.h"

CombatBehavior::CombatBehavior()
	: mType(), mCreature(), mIsAttacking(false), mData() {}

CombatBehavior::CombatBehavior(Creature& node, const CreatureData& data)
	: mType(node.getType()), mCreature(&node), mIsAttacking(false), mData(data) {}

CombatBehavior::~CombatBehavior() {}

void CombatBehavior::updateCombatPattern(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos) {}

void CombatBehavior::checkCooldown(sf::Time dt, sf::Vector2f playerPos)
{
	// Procedure for checking cooldowns:
	// 1: Decriment cooldown interval
	// 2: Check that the attack interval is not currently going on. If that is the case, return, since
	//    the Creature should still be in their attack posture
	// 2: Check for Player asking for an attack when the attack is on cooldown and not being performed
	//		Conditions:
	//			- mIsAttacking is currently true
	//			- the attack is still on cooldown
	//	  If so, set mIsAttacking to false and return
	// 3: Check if the cooldown has hit zero.  If so, set mIsAttacking to true, reset cooldown and return
}

void CombatBehavior::checkInterval(sf::Time dt, CommandQueue& commands) {}

bool CombatBehavior::isAttacking() const { return mIsAttacking; }

void CombatBehavior::attack() { mIsAttacking = true; }

void CombatBehavior::attack(sf::Vector2f playerPos) {}

Command CombatBehavior::getCommand() { return Command{}; }