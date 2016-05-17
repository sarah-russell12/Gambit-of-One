/*
NoCombatBehavior.cpp

Date Created: May 16, 2016

Defines all the functions declared in NoCombatBehavior.h
*/

#include "NoCombatBehavior.h"

NoCombatBehavior::NoCombatBehavior(Creature::Type type, SceneNode& node)
	: CombatBehavior(type, node)
{

}

NoCombatBehavior::~NoCombatBehavior() {}

void NoCombatBehavior::checkAttacks(sf::Time dt, CommandQueue& commands, sf::Vector2f playerPos)
{
	// A creature with no combat behavior does nothing
}