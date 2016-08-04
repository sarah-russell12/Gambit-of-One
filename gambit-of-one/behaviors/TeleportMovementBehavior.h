/*
TeleportMovementBehavior.h

Date Created: June 13, 2016

Teleport movement behavior is when a creature moves from one point to another 
point instantaneously.  This is used for creatures who are magic, or are just
really, really, *really* fast.
*/

#pragma once
#ifndef TELEPORT_MOVEMENT_BEHAVIOR_H
#define TELEPORT_MOVEMENT_BEHAVIOR_H

#include "MovementBehavior.h"

class TeleportMovementBehavior : public MovementBehavior
{
public:
	TeleportMovementBehavior(Creature& node, const CreatureData& data);
	~TeleportMovementBehavior();

	virtual void		updateMovementPattern(sf::Time dt);
	virtual void		checkCompass();
	virtual void		checkAggro();

private:
	std::size_t						mPointIndex;
	sf::Time						mTeleportCooldown;
};

#endif // TELEPORT_MOVEMENT_BEHAVIOR_H
