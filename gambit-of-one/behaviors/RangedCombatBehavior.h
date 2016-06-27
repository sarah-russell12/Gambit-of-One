/*
RangedCombatBehavior.h

Date Created: May 16, 2016

Ranged combat is using weapons that can shoot projectiles from a distance.
RangedCombatBehavior creates projectiles that move across the screen linearly.
*/
#pragma once
#ifndef RANGED_COMBAT_BEHAVIOR_H
#define RANGED_COMBAT_BEHAVIOR_H

#include "CombatBehavior.h"
#include "Command.hpp"
#include "CommandQueue.hpp"
#include "DataTables.hpp"
#include "Projectile.hpp"
#include "ResourceHolder.hpp"

class RangedCombatBehavior : public CombatBehavior
{
public:
	RangedCombatBehavior(Creature& node, const TextureHolder& textures);
	~RangedCombatBehavior();

	virtual void		updateCombatPattern(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos);
	virtual void		checkCooldown(sf::Time dt, sf::Vector2f playerPos);
	virtual void		attack();

private:
	virtual void		checkInterval(sf::Time dt, CommandQueue& commands);

	void				attack(CommandQueue& commands);
	void				createArrow(SceneNode& node, const TextureHolder& textures) const;
	
private:
	Command			mFireCommand;
	bool			mIsFiring;
};

#endif //RANGED_COMBAT_BEHAVIOR_H
