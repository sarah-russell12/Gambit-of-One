/*
CombatBehavior.h

Date Created: May 16, 2016

Date Last Updated: May 25, 2016

CombatBehavior is the set of actions that a Creature takes in combat.
CombatBehaviors differ from creature to creature.

Updates:
	- May 25, 2016: Added isAttacking() method, which is necessary for 
					determining which creature frames to render.
*/

#pragma once
#ifndef COMBAT_BEHAVIOR_H
#define COMBAT_BEHAVIOR_H

#include "Creature.hpp"
#include "Command.hpp"
#include "CommandQueue.hpp"
#include "DataStructures.h"

class CombatBehavior
{
public:
	CombatBehavior();			// Default Constructor
	CombatBehavior(Creature& node, const CreatureData& data);
	~CombatBehavior();

	virtual void		updateCombatPattern(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos);
	virtual void		checkCooldown(sf::Time dt, sf::Vector2f playerPos);

	virtual bool		isAttacking() const;
	
	virtual void		attack();

private:
	virtual void		checkInterval(sf::Time dt, CommandQueue& commands);
	virtual void		attack(sf::Vector2f playerPos);
	virtual Command		getCommand();

protected:
	Creature*			mCreature;
	Creature::Type		mType;

	CreatureData		mData;
	sf::Time			mAttackCooldown;
	sf::Time			mAttackInterval;
	bool				mIsAttacking;
};

#endif //COMBAT_BEHAVIOR_H