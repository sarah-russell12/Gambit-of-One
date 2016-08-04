/*
TeleportMovementBehavior.cpp

Date Created: June 13, 2016

Defines all the methods declared in TeleportMovementBehavior.h
*/

#include "TeleportMovementBehavior.h"

TeleportMovementBehavior::TeleportMovementBehavior(Creature& creature, const CreatureData& data)
	: MovementBehavior(creature, data), mPointIndex(0), mTeleportCooldown(data.attackInterval) {}
// The idea with the teleport cooldown being the attack interval is that the 
// creature will attack after a teleport... hopefully

TeleportMovementBehavior::~TeleportMovementBehavior() {}

void TeleportMovementBehavior::updateMovementPattern(sf::Time dt)
{
	mTeleportCooldown -= dt;
	if (mTeleportCooldown <= sf::Time::Zero)
	{
		auto& points = mData.teleportPoints;
		mPointIndex = (mPointIndex + 1) % points.size();
		auto point = points[mPointIndex];
		mCreature->setPosition(point.pos);
		mCompass = point.compass;
		mTeleportCooldown = mData.attackInterval;
	}
}

void TeleportMovementBehavior::checkAggro()
{
	if (!mIsAggroed)
	{
		mIsAggroed = true;
	}
}

void TeleportMovementBehavior::checkCompass()
{
	mCompass = mData.teleportPoints[mPointIndex].compass;
}