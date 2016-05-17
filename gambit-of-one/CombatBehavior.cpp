/*
CombatBehavior.cpp

Date Created: May 16, 2016

Defines the non pure virtual functions declared in CombatBehavior.h
*/

#include "CombatBehavior.h"

CombatBehavior::CombatBehavior(Creature::Type type, SceneNode& node)
	: mType(type), mNode(&node), mIsAttacking(false), mAttackInterval(), mAttackCooldown() {}

CombatBehavior::~CombatBehavior() {}