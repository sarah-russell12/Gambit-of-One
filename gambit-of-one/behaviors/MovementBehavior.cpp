/*
MovementBehavior.cpp

Date Created: May 30, 2016

Defines all the methods declared in MovementBehavior.h
*/

#include "MovementBehavior.h"

MovementBehavior::MovementBehavior()
	: mType(), mCreature(), mIsAggroed(false), mIsBlocked(false), mTargetDirection(), mTargetPosition() {}

MovementBehavior::MovementBehavior(Creature& node, const CreatureData& data)
	: mType(node.getType())
	, mCreature(&node)
	, mIsAggroed(false)
	, mIsBlocked(false)
	, mTargetDirection() 
	, mTargetPosition()
	, mData(data) {}

MovementBehavior::~MovementBehavior() {}

Compass MovementBehavior::getCompass() const
{
	return mCompass;
}

bool MovementBehavior::isAggroed() const
{
	return mIsAggroed;
}

bool MovementBehavior::isBlocked() const
{
	return mIsBlocked;
}

void MovementBehavior::block()
{
	mIsBlocked = true;
}

void MovementBehavior::unblock()
{
	mIsBlocked = false;
}

void MovementBehavior::updateMovementPattern(sf::Time dt) {}

void MovementBehavior::guide(sf::Vector2f pos) {}

void MovementBehavior::checkAggro() {}

void MovementBehavior::checkCompass() 
{
	sf::Vector2f vel = mCreature->getVelocity();
	if (!mIsBlocked)
	{
		if (abs(vel.x) > abs(vel.y))
		{
			if (vel.x > 0)
				mCompass = East;
			else
				mCompass = West;
		}
		else if (!(vel.x == 0 && vel.y == 0))
		{
			if (vel.y > 0)
				mCompass = South;
			else
				mCompass = North;
		}
	}
}