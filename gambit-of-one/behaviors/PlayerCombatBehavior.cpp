/*
PlayerCombatBehavior.cpp

Date Created: May 25, 2016

Defines all the methods declared in PlayerCombatBehavior.h
*/

#include "PlayerCombatBehavior.h"
 
PlayerCombatBehavior::PlayerCombatBehavior(Creature& node)
	: CombatBehavior(node), mMelee(node), mRanged(node) {}

PlayerCombatBehavior::~PlayerCombatBehavior() {}

void PlayerCombatBehavior::updateCombatPattern(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos)
{
	if (mMelee.isAttacking())
	{
		// update the Melee Combat Pattern, check the cooldowns on all other 
		// combat behaviors
		mMelee.updateCombatPattern(dt, commands, playerPos);
		mRanged.checkCooldown(dt, playerPos);
	}
	else if (mRanged.isAttacking())
	{
		// update the Ranged Combat Pattern, check the cooldowns on all other
		// combat behaviors
		mRanged.updateCombatPattern(dt, commands, playerPos);
		mMelee.checkCooldown(dt, playerPos);
	}
	else
	{
		// just check cooldowns
		mMelee.checkCooldown(dt, playerPos);
		mRanged.checkCooldown(dt, playerPos);
		setAction(Player::ActionCount);
		return;
	}
}

bool PlayerCombatBehavior::isAttacking() const
{
	return mMelee.isAttacking() || mRanged.isAttacking();
}

void PlayerCombatBehavior::attack()
{
	// Make sure that no other type of attack is happening
	switch (mAction)
	{
	case Player::Attack:
		if (!mRanged.isAttacking()) mMelee.attack();
		break;
	case Player::Fire:
		if (!mMelee.isAttacking()) mRanged.attack();
		break;
	default:
		break;
	}
}

int PlayerCombatBehavior::getTileMultiplier() const
{
	switch(mAction)
	{
	case Player::Fire:
		return 1;
	case Player::Attack:
		return 2;
	default:
		return 0;
	}
}

void PlayerCombatBehavior::setStats()
{
	mMelee.setStats();
	mRanged.setStats();
}
