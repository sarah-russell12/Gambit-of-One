/*
CombatBehavior.h

Date Created: May 16, 2016

CombatBehavior is the set of actions that a Creature takes in combat.
CombatBehaviors differ from creature to creature.
*/

#pragma once
#ifndef COMBAT_BEHAVIOR_H
#define COMBAT_BEHAVIOR_H

#include "Command.hpp"
#include "CommandQueue.hpp"
#include "Creature.hpp"
#include "DataTables.hpp"
#include "SceneNode.hpp"

class CombatBehavior
{
public:
	CombatBehavior(Creature::Type type, SceneNode& node);
	~CombatBehavior();

	virtual void		checkAttacks(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos) = 0;

private:
	virtual void		attack(sf::Vector2f playerPos) = 0;
	virtual Command		getCommand() = 0;

protected:
	sf::Time			mAttackInterval;
	sf::Time			mAttackCooldown;
	bool				mIsAttacking;

	Creature::Type		mType;
	SceneNode*			mNode;
};

#endif //COMBAT_BEHAVIOR_H