/*
BehaviorFactory.h

Date Created: May 24, 2016

A simple factory for instanciating behavior classes for creatures.
Will return different behaviors based upon the creature interacting with it.
*/

#pragma once
#ifndef BEHAVIOR_FACTORY_H
#define BEHAVIOR_FACTORY_H

#include "CombatBehavior.h"

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class BehaviorFactory
{
public:
	enum CombatStyle
	{
		Player,
		DontFight,
		Melee,
		Ranged,
	};

	enum Movement
	{
		DontMove,
		Directional,
		Guided,
		Teleporting,
		Turning,
	};

public:
	BehaviorFactory();
	~BehaviorFactory();

	CombatBehavior*							getCombatBehavior(Creature& node, CombatStyle combat);
	MovementBehavior*						getMovementBehavior(Creature& node, Movement move);

};

#endif //BEHAVIOR_FACTORY_H
