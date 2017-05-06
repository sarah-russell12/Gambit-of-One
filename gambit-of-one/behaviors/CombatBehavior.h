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

#include "Player.hpp"
#include "Creature.hpp"
#include "Command.hpp"
#include "CommandQueue.hpp"
#include "DataTables.hpp"

class CombatBehavior
{
public:
	CombatBehavior();			// Default Constructor
	CombatBehavior(Creature& node);
	~CombatBehavior();

	virtual void		updateCombatPattern(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos);
	virtual void		checkCooldown(sf::Time dt, sf::Vector2f playerPos);

	virtual bool		isAttacking() const;
	
	virtual void		attack();

	virtual void		setAction(Player::Action action);
	Player::Action		getAction() const;

	virtual int			getTileMultiplier() const;
	virtual void		setStats();
	
	unsigned int		getDamage(unsigned int main, unsigned int limiter);

private:
	virtual void		checkInterval(sf::Time dt, CommandQueue& commands);
	virtual void		attack(sf::Vector2f playerPos);
	virtual Command		getCommand();

protected:
	Creature*			mCreature;

	sf::Time			mAttackInterval;
	sf::Time			mAttackCooldown;
	bool				mIsAttacking;

	Player::Action		mAction;
};

#endif //COMBAT_BEHAVIOR_H