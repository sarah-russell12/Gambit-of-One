/*
DirectionalMovementBehavior.cpp

Date Created: May 31, 2016

Defines all the methods declared in DirectionalMovementBehavior.h
*/

#include "DirectionalMovementBehavior.h"
#include "Utility.hpp"

DirectionalMovementBehavior::DirectionalMovementBehavior(Creature& node, const CreatureData& data)
	: MovementBehavior(node, data), mDirectionIndex(0), mTravelledDistance(0.f) {}

DirectionalMovementBehavior::~DirectionalMovementBehavior() {}

void DirectionalMovementBehavior::updateMovementPattern(sf::Time dt)
{

	if (mTravelledDistance > mData.directions[mDirectionIndex].distance)
	{
		mDirectionIndex = (mDirectionIndex + 1) % mData.directions.size();
		mTravelledDistance = 0.f;
	}

	float radians = toRadian(mData.directions[mDirectionIndex].angle + 90.f);
	float vx = mCreature->getMaxSpeed() * std::cos(radians);
	float vy = mCreature->getMaxSpeed() * std::sin(radians);
	mCreature->setVelocity(vx, vy);
	mTravelledDistance += mCreature->getMaxSpeed() * dt.asSeconds();
}

void DirectionalMovementBehavior::guide(sf::Vector2f pos) 
{
	mTargetDirection = unitVector(pos - mCreature->getWorldPosition());
}

void DirectionalMovementBehavior::checkAggro()
{
	sf::Vector2f myPosition = mCreature->getWorldPosition();
	float distance = length(mTargetPosition - myPosition);
	if (distance <= mData.aggroDistance && !mCreature->isAllied())
	{
		mIsAggroed = true;
	}
}

void DirectionalMovementBehavior::checkCompass()
{
	// Will look in the direction they are moving if not aggroed, but will look
	// towards the player if they are aggroed
	if (!mIsBlocked)
	{
		if (!mIsAggroed)
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
		else
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
	}
}