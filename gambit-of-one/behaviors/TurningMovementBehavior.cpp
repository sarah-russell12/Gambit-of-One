/*
TurningMovementBehavior.cpp

Date Created: May 31, 2016

Defines all the methods declared in TurningMovementBehavior.h
*/

#include "TurningMovementBehavior.h"
#include "Utility.hpp"

TurningMovementBehavior::TurningMovementBehavior(Creature& node)
	: MovementBehavior(node)
{
	// A creature with a turning behavior will always turn towards the player
	mIsAggroed = true;
}

TurningMovementBehavior::~TurningMovementBehavior() {}

void TurningMovementBehavior::updateMovementPattern(sf::Time dt)
{
	// just turn towards the player
	checkCompass();
}

void TurningMovementBehavior::guide(sf::Vector2f pos)
{
	mTargetDirection = mTargetDirection = unitVector(pos - mCreature->getWorldPosition());
}

void TurningMovementBehavior::checkCompass()
{
	if (abs(mTargetDirection.x) > abs(mTargetDirection.y))
	{
		if (mTargetDirection.x > 0)
			mCompass = East;
		else
			mCompass = West;
	}
	else if (!(mTargetDirection.x == 0 && mTargetDirection.y == 0))
	{
		if (mTargetDirection.y > 0)
			mCompass = South;
		else
			mCompass = North;
	}
}

void TurningMovementBehavior::checkAggro()
{
	if (!mIsAggroed)
	{
		mIsAggroed = true;
	}
}