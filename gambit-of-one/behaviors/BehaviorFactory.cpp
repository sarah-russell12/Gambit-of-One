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

CombatBehavior* BehaviorFactory::getCombatBehavior(Creature& node, CombatStyle combat)
{
	switch (combat)
	{
	case Melee:
		return new MeleeCombatBehavior(node);
	case Ranged:
		return new RangedCombatBehavior(node);
	case Player:
		return new PlayerCombatBehavior(node);
	default:
		return new NoCombatBehavior(node);
	}
}

MovementBehavior* BehaviorFactory::getMovementBehavior(Creature& node, Movement move)
{
	switch (move)
	{
	case Directional:
		return new DirectionalMovementBehavior(node);
	case Guided:
		return new GuidedMovementBehavior(node);
	case Teleporting:
		return new TeleportMovementBehavior(node);
	case Turning:
		return new TurningMovementBehavior(node);
	case DontMove:
		return new MovementBehavior(node);	
	}
}