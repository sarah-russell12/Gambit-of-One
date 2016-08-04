/*
MovementBehavior.h

Date Created: May 30, 2016

Further abstracting the behaviors of creatures, movement behaviors will vary
from creature to creature.
*/

#pragma once
#ifndef MOVEMENT_BEHAVIOR_H
#define MOVEMENT_BEHAVIOR_H

#include "ResourceIdentifiers.hpp"
#include "DataStructures.h"
#include "Creature.hpp"

class MovementBehavior
{
public:
	MovementBehavior();					// default constructor
	MovementBehavior(Creature& node, const CreatureData& data);
	~MovementBehavior();

	Compass				getCompass() const;
	bool				isAggroed() const;
	bool				isBlocked() const;

	void				block();
	void				unblock();

	virtual void		updateMovementPattern(sf::Time dt);
	virtual void		guide(sf::Vector2f pos);
	virtual void		checkCompass();
	virtual void		checkAggro();

protected:
	Creature*			mCreature;
	Creature::Type		mType;
	CreatureData		mData;

	Compass				mCompass;
	bool				mIsAggroed;
	bool				mIsBlocked;
	sf::Vector2f		mTargetDirection;
	sf::Vector2f		mTargetPosition;

};

#endif //MOVEMENT_BEHAVIOR_H
