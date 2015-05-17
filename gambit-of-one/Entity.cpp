#include "Entity.h"

Entity::Entity(int hitPoints)
	: mHitPoints(hitPoints) {}

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

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands) {
	move(mVelocity * dt.asSeconds());
}

int Entity::getHitpoints() const
{
	return mHitPoints;
}

bool Entity::isDestroyed() const
{
	return mHitPoints <= 0;
}

void Entity::repair(int points)
{
	assert(points > 0);

	mHitPoints += points;
}

void Entity::damage(int points)
{
	assert(points > 0);

	mHitPoints -= points;
}

void Entity::destroy()
{
	mHitPoints = 0;
}