/*
DirectionalMovementBehavior.h

Date Created: May 31, 2016

In the original game from the textbook, the enemy aircrafts had a movement 
behavior where they would move in a predetermined pattern.  I don't know
where it may find its use in game, but having something and not needing it
is better than needing something but not having it.

The way the creature turns with this behavior is also different.  They will
look in the direction they are going if not aggroed, but will look towards
the player if they are.
*/

#pragma once
#ifndef DIRECTIONAL_MOVEMENT_BEHAVIOR_H
#define DIRECTIONAL_MOVEMENT_BEHAVIOR_H

#include "MovementBehavior.h"

class DirectionalMovementBehavior : public MovementBehavior
{
public:
	DirectionalMovementBehavior(Creature& node, const CreatureData& data);
	~DirectionalMovementBehavior();

	virtual void	updateMovementPattern(sf::Time dt);
	virtual void	guide(sf::Vector2f pos);
	virtual void	checkCompass();
	virtual void	checkAggro();

private:
	std::size_t					mDirectionIndex;
	float						mTravelledDistance;
};

#endif // DIRECTIONAL_MOVEMENT_BEHAVIOR_H
