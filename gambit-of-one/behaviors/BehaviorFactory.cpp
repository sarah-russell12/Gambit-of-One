/*
BehaviorFactory.cpp

Date Created: May 24, 2016

Defines all the methods declared in BehaviorFactory.h
*/

#include "BehaviorFactory.h"

BehaviorFactory::BehaviorFactory()
	: mProjectileTextures()
{
	loadProjectileTextures();
}

BehaviorFactory::~BehaviorFactory() {}

CombatBehavior BehaviorFactory::getCombatBehavior(Creature::Type type, SceneNode& node)
{
	switch (type)
	{
	case Creature::Rat:
	case Creature::Bandit:
		return MeleeCombatBehavior(type, node);
	case Creature::Archer:
		return RangedCombatBehavior(type, node, mProjectileTextures);
	case Creature::Hero:
		// TODO: Add instantiation of PlayerCombatBehavior
		break;
	}
}


void BehaviorFactory::loadProjectileTextures()
{
	mProjectileTextures.load(Textures::Arrow, "../Media/Textures/Arrow.png");
}