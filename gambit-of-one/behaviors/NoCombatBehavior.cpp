/*
NoCombatBehavior.cpp

Date Created: May 16, 2016

Defines all the functions declared in NoCombatBehavior.h
*/

#include "NoCombatBehavior.h"

NoCombatBehavior::NoCombatBehavior(Creature& node, const CreatureData& data)
	: CombatBehavior(node, data)
{

}

NoCombatBehavior::~NoCombatBehavior() {}

void NoCombatBehavior::updateCombatPattern(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos)
{
	// A creature with no combat behavior does nothing
}