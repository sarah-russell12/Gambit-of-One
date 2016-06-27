/*
MeleeCombatBehavior.h

Date Created: May 16, 2016

Melee is attacking with anything that is not some sort of ranged weapon.
Examples are fighting with fists, swords, and axes.  MeleeCombatBehavior makes
a Creature lash out at a percieved enemy if they are up close to them.
Melee is also very hard to spell correctly in one try...
*/
#pragma once
#ifndef MELEE_COMBAT_BEHAVIOR_H
#define MELEE_COMBAT_BEHAVIOR_H

#include "CombatBehavior.h"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class MeleeCombatBehavior : public CombatBehavior
{
public:
	MeleeCombatBehavior(Creature& node);
	~MeleeCombatBehavior();

	virtual void		updateCombatPattern(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos);
	virtual void		checkCooldown(sf::Time dt, sf::Vector2f playerPos);
	virtual void		attack();

private:
	virtual void		checkInterval(sf::Time dt, CommandQueue& commands);
	virtual void		attack(sf::Vector2f playerPos);

};

#endif //MELEE_COMBAT_BEHAVIOR_H
