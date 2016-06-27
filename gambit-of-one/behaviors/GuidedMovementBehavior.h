/*
GuidedMovementBehavior.h

Date Created: May 31, 2016

Guided movement behavior is a behavior that guides the creature towards the 
player's position on screen.
*/

#pragma once
#ifndef	GUIDED_MOVEMENT_BEHAVIOR_H
#define GUIDED_MOVEMENT_BEHAVIOR_H

#include "MovementBehavior.h"

class GuidedMovementBehavior : public MovementBehavior
{
public:
	GuidedMovementBehavior(Creature& node);
	~GuidedMovementBehavior();

	virtual void		updateMovementPattern(sf::Time dt);
	virtual void		guide(sf::Vector2f pos);
	virtual void		checkCompass();
	virtual void		checkAggro();
};

#endif // GUIDED_MOVEMENT_BEHAVIOR_H
