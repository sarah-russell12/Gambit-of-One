/*
TeleportMovementBehavior.cpp

Date Created: June 13, 2016

Defines all the methods declared in TeleportMovementBehavior.h
*/

#include "TeleportMovementBehavior.h"

TeleportMovementBehavior::TeleportMovementBehavior(Creature& creature)
	: MovementBehavior(creature), mPointIndex(0), mTeleportCooldown() 
	{
		mTeleportCooldown = sf::seconds(7.f - 0.5f * creature.getData().intelligence);
	}
// The idea with the teleport cooldown being the attack interval is that the 
// creature will attack after a teleport... hopefully

TeleportMovementBehavior::~TeleportMovementBehavior() {}

void TeleportMovementBehavior::updateMovementPattern(sf::Time dt)
{
	mTeleportCooldown -= dt;
	if (mTeleportCooldown <= sf::Time::Zero)
	{
		auto& points = mCreature->getData().teleportPoints;
		mPointIndex = (mPointIndex + 1) % points.size();
		auto point = points[mPointIndex];
		mCreature->setPosition(point.pos);
		mCompass = point.compass;
		// The smarter the teleporter, the faster they teleport
		mTeleportCooldown = sf::seconds(7.f - 0.5f * mCreature->getData().intelligence);
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
	mCompass = mCreature->getData().teleportPoints[mPointIndex].compass;
}