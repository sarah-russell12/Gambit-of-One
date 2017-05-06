/*
CombatBehavior.cpp

Date Created: May 16, 2016

Defines the non pure virtual functions declared in CombatBehavior.h
*/

#include "CombatBehavior.h"

#include <cmath>
#include <random>
#include <ctime>

CombatBehavior::CombatBehavior()
	: mCreature(), mIsAttacking(false), mAttackInterval(), mAttackCooldown() {}

CombatBehavior::CombatBehavior(Creature& node)
	: mCreature(&node), mIsAttacking(false), mAttackInterval(), mAttackCooldown() {}

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

void CombatBehavior::setAction(Player::Action action) { mAction = action; }

Player::Action CombatBehavior::getAction() const { return mAction; }

int CombatBehavior::getTileMultiplier() const { return 1; }

unsigned int CombatBehavior::getDamage(unsigned int main, unsigned int limiter)
{
	std::default_random_engine generator(time(0));
	std::uniform_int_distribution<int> dist6(1, 6);
	std::uniform_int_distribution<int> dist4(1, 4);
	auto roll_d6 = std::bind(dist6, generator);
	auto roll_d4 = std::bind(dist4, generator);

	int diff;
	if (limiter < (main / 2))
	{
		diff = (main / 2) - limiter;
	}
	else diff = 0;

	int damage = 0;
	for (int i = 0; i < main; i++)
	{
		damage += roll_d6();
	}
	for (int j = 0; j < diff; j++)
	{
		damage -= roll_d4();
	}
	return damage;
}

void CombatBehavior::setStats() {}