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

CombatBehavior* BehaviorFactory::getCombatBehavior(Creature& node)
{
	switch (node.getType())
	{
	case Creature::Rat:
	case Creature::Bandit:
		return new MeleeCombatBehavior(node);
	case Creature::Archer:
		return new RangedCombatBehavior(node);
	case Creature::Hero:
		// TODO: Add instantiation of PlayerCombatBehavior
		return new PlayerCombatBehavior(node);
	default:
		return new NoCombatBehavior(node);
	}
}

MovementBehavior* BehaviorFactory::getMovementBehavior(Creature& node)
{
	switch (node.getType())
	{
	case Creature::Rat:
	case Creature::Bandit:
		return new GuidedMovementBehavior(node);
	case Creature::Archer:
		return new TurningMovementBehavior(node);
	case Creature::Hero:
		return new MovementBehavior(node);
	default:
		// the player's character is moved differently thus it requires no 
		// automated movement
		return new MovementBehavior();
	}
}