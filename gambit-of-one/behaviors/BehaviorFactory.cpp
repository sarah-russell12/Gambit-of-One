/*
BehaviorFactory.cpp

Date Created: May 24, 2016

Defines all the methods declared in BehaviorFactory.h
*/

#include "BehaviorFactory.h"
#include "ResourceIdentifiers.hpp"

#include "MeleeCombatBehavior.h"
#include "NoCombatBehavior.h"
#include "RangedCombatBehavior.h"
#include "PlayerCombatBehavior.h"

#include "DirectionalMovementBehavior.h"
#include "GuidedMovementBehavior.h"
#include "TeleportMovementBehavior.h"
#include "TurningMovementBehavior.h"

BehaviorFactory::BehaviorFactory() {}

BehaviorFactory::~BehaviorFactory() {}

CombatBehavior* BehaviorFactory::getCombatBehavior(Creature& node, const CreatureData& data)
{
	switch (node.getType())
	{
	case Creature::Rat:
	case Creature::Bandit:
		return new MeleeCombatBehavior(node, data);
	case Creature::Archer:
		return new RangedCombatBehavior(node, data);
	case Creature::Hero:
		return new PlayerCombatBehavior(node, data);
	default:
		return new NoCombatBehavior(node, data);
	}
}

MovementBehavior* BehaviorFactory::getMovementBehavior(Creature& node, const CreatureData& data)
{
	switch (node.getType())
	{
	case Creature::Rat:
	case Creature::Bandit:
		return new GuidedMovementBehavior(node, data);
	case Creature::Archer:
		return new TurningMovementBehavior(node, data);
	case Creature::Hero:
		return new MovementBehavior(node, data);
	default:
		// the player's character is moved differently thus it requires no 
		// automated movement
		return new MovementBehavior();
	}
}