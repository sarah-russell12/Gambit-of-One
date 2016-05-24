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
#include "..\ResourceHolder.hpp"
#include "..\ResourceIdentifiers.hpp"

class MeleeCombatBehavior : public CombatBehavior
{
public:
	MeleeCombatBehavior(Creature::Type type, SceneNode& node);
	~MeleeCombatBehavior();

	virtual void		checkAttacks(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos);

private:
	virtual void		attack(sf::Vector2f playerPos);

};

#endif //MELEE_COMBAT_BEHAVIOR_H
