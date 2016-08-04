/*
PlayerCombatBehavior.h

Date Created: May 24, 2016

The player is capable of melee, ranged and (eventually) magic combat.  So the
CombatBehavior of the player's character should manage all three of those. I
have no clue if there is a more efficient way of going about this.
*/

#pragma once
#ifndef PLAYER_COMBAT_BEHAVIOR_H
#define PLAYER_COMBAT_BEHAVIOR_H

#include "CombatBehavior.h"
#include "MeleeCombatBehavior.h"
#include "RangedCombatBehavior.h"
#include "Player.hpp"

class PlayerCombatBehavior : public CombatBehavior
{
public:
	PlayerCombatBehavior(Creature& node);
	~PlayerCombatBehavior();

	virtual void		updateCombatPattern(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos);

	virtual bool		isAttacking(Player::Action action) const;
	void				attack(Player::Action action);

private:
	MeleeCombatBehavior		mMelee;
	RangedCombatBehavior	mRanged;
};

#endif //PLAYER_COMBAT_BEHAVIOR_H