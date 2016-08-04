/*
PlayerCreature.cpp

Date Created: June 13, 2016

Defines all the methods declared in PlayerCreature.h
*/

#include "PlayerCreature.h"
#include "Utility.hpp"
#include "MovementBehavior.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


PlayerCreature::PlayerCreature(Type type, const CreatureData& data, DataTable* table)
	: Creature(type, data, table), mCombatBehavior(*this, data), mKillCount(0)
{

}

unsigned int PlayerCreature::getCategory() const
{
	return Category::PlayerCreature;
}

int PlayerCreature::getKillCount() const
{
	return mKillCount;
}

bool PlayerCreature::isAttacking(Player::Action action) const
{
	return mCombatBehavior.isAttacking(action);
}

void PlayerCreature::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}


void PlayerCreature::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	updateSprite();

	if (mMoveBehavior->isBlocked())
	{
		mMoveBehavior->unblock();
	}

	if (isDestroyed())
	{
		mIsMarkedForRemoval = true;
		return;
	}

	mCombatBehavior.updateCombatPattern(dt, commands, getPosition());

	Entity::updateCurrent(dt, commands);
	Creature::updateTexts();
}

void PlayerCreature::updateSprite()
{
	sf::IntRect textureRect = mSprite.getTextureRect();
	textureRect.top = 0;
	textureRect.left = 0;

	mMoveBehavior->checkCompass();
	switch (getCompass())
	{
	case Compass::South:
		textureRect.left = 0;
		break;
	case Compass::East:
		textureRect.left += textureRect.width;
		break;
	case Compass::North:
		textureRect.left += 2 * textureRect.width;
		break;
	case Compass::West:
		textureRect.left += 3 * textureRect.width;
		break;
	}

	// Check for attacking
	if (mCombatBehavior.isAttacking(Player::Fire))
		textureRect.top += textureRect.height;
	if (mCombatBehavior.isAttacking(Player::Attack))
		textureRect.top += 2 * textureRect.height;

	mSprite.setTextureRect(textureRect);
}

void PlayerCreature::attack(Player::Action action)
{
	mCombatBehavior.attack(action);
}

void PlayerCreature::incrementKillCount()
{
	mKillCount += 1;
}