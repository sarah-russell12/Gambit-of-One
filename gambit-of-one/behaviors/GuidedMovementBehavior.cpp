/*
GuidedMovementBehavior.cpp

Date Created: May 31 2016

Defines all the methods declared in GuidedMovementBehavior.h
*/

#include "GuidedMovementBehavior.h"
#include "DataTables.hpp"
#include "Utility.hpp"

GuidedMovementBehavior::GuidedMovementBehavior(Creature& node)
	: MovementBehavior(node) {}

GuidedMovementBehavior::~GuidedMovementBehavior() {}

void GuidedMovementBehavior::updateMovementPattern(sf::Time dt)
{
	checkAggro();
	if (mIsAggroed)
	{
		const float approachRate = mCreature->getMaxSpeed();

		sf::Vector2f newVelocity(0.f, 0.f);

		if (approachRate != 0.f)
		{
			newVelocity += unitVector(approachRate * dt.asSeconds() * mTargetDirection + (mCreature->getVelocity() * 0.5f));
			newVelocity *= mCreature->getMaxSpeed();
		}

		mCreature->setVelocity(newVelocity);
	}
}

void GuidedMovementBehavior::guide(sf::Vector2f pos)
{
	mTargetPosition = pos;
	mTargetDirection = unitVector(pos - mCreature->getWorldPosition());
}

void GuidedMovementBehavior::checkAggro()
{
	sf::Vector2f myPosition = mCreature->getWorldPosition();
	float distance = length(mTargetPosition - myPosition);
	if (distance <= mCreature->getData().aggroDistance)
	{
		mIsAggroed = true;
	}	
}

void GuidedMovementBehavior::checkCompass()
{
	if (!mIsBlocked)
	{
		sf::Vector2f velocity = mCreature->getVelocity();
		if (abs(velocity.x) > abs(velocity.y))
		{
			if (velocity.x > 0)
				mCompass = East;
			else
				mCompass = West;
		}
		else if (!(velocity.x == 0 && velocity.y == 0))
		{
			if (velocity.y > 0)
				mCompass = South;
			else
				mCompass = North;
		}
	}
}