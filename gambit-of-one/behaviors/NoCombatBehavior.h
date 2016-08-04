/*
NoCombatBehavior.h

Date Created: May 16, 2016

NoCombatBehavior is essentially what one would think it is.  This creature 
doesn't attack.  This behavior is designed for NPCs to use.  This clears up
the issue of how I am to prevent an NPC from attempting to tear off the
player's face.
*/

#pragma once
#ifndef	NO_COMBAT_BEHAVIOR_H
#define NO_COMBAT_BEHAVIOR_H

#include "CombatBehavior.h"

class NoCombatBehavior : public CombatBehavior
{
public:
	NoCombatBehavior(Creature& node, const CreatureData& data);
	~NoCombatBehavior();

	virtual void		updateCombatPattern(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos);
};

#endif //NO_COMBAT_BEHAVIOR_H