/*
Entity.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/

#include"Entity.hpp"

#include <cassert>


Entity::Entity(int hitpoints)
	: mVelocity()
	, mHitpoints(hitpoints)
	, mImmunity(false)
	, mImmunityCountdown()
{
	//mCompass = South;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

int Entity::getHitpoints() const
{
	return mHitpoints;
}

void Entity::repair(int points)
{
	assert(points > 0);

	mHitpoints += points;
}

void Entity::damage(int points)
{
	assert(points > 0);
	mHitpoints -= points;
	mImmunity = true;
}

void Entity::destroy()
{
	mHitpoints = 0;
}

bool Entity::isDestroyed() const
{
	return mHitpoints <= 0;
}

bool Entity::isImmune() const
{
	if (mImmunityCountdown > sf::Time::Zero)
		return true;
	return false;
}

void Entity::checkImmunity(sf::Time dt)
{
	if (mImmunity && mImmunityCountdown <= sf::Time::Zero)
	{
		// Restart Immunity Timer
		mImmunityCountdown += sf::seconds(3);
		mImmunity = false;
	}
	else if (mImmunityCountdown > sf::Time::Zero)
	{
		// Interval not expired: Decrease it further
		mImmunityCountdown -= dt;
		mImmunity = false;
	}
}

void Entity::updateCurrent(sf::Time dt, CommandQueue&)
{
	move(mVelocity * dt.asSeconds());	
	checkImmunity(dt);
}

