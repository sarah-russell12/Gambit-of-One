/*
TurningMovementBehavior.h

Date Created: May 31, 2016

Turning movement behavior is when a creature will not move anywhere, but just
turn towards the player's position.
*/

#pragma once
#ifndef TURNING_MOVEMENT_BEHAVIOR_H
#define TURNING_MOVEMENT_BEHAVIOR_H

#include "MovementBehavior.h"

class TurningMovementBehavior : public MovementBehavior
{
public:
	TurningMovementBehavior(Creature& node);
	~TurningMovementBehavior();

	virtual void	updateMovementPattern(sf::Time dt);
	virtual void	guide(sf::Vector2f pos);
	virtual void	checkCompass();
	virtual void	checkAggro();
};

#endif // TURNING_MOVEMENT_BEHAVIOR_H
