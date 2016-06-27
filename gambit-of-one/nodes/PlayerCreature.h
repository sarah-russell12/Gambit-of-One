/*
PlayerCreature.h

Date Created: June 13, 2016

PlayerCreature refers to the hero the player controls in the game
Since the combat and movement behaviors the player users is not as 
cookie-cutter as other creatures, and has interface elements that are
distinct from other Creatures, it should have its own class.
*/
#pragma once
#ifndef PLAYER_CREATURE_H
#define PLAYER_CREATURE_H

#include "Creature.hpp"
#include "PlayerCombatBehavior.h"
#include "Player.hpp"

class PlayerCreature : public Creature
{
public:
	PlayerCreature(Type type, const TextureHolder& textures, const FontHolder& fonts);

	virtual unsigned int			getCategory() const;
	bool							isAttacking(Player::Action) const;
	
	void							attack(Player::Action action);

private:
	virtual void					drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void 					updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void					updateSprite();

private:
	PlayerCombatBehavior			mCombatBehavior;
};

#endif // PLAYER_CREATURE_H