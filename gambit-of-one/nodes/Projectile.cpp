/*
Projectile.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/

#include "Projectile.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <cassert>


Projectile::Projectile(Type type, const TextureHolder& textures, const Compass& direction, const ProjectileData& data)
	: Entity(1)
	, mType(type)
	, mSprite(textures.get(data.texture))
	, mTargetDirection()
	, mCDirection(direction)
	, mData(data)
{
	switch (direction)
	{
	case Compass::North:
		break;
	case Compass::East:
		mSprite.rotate(90);
		break;
	case Compass::South:
		mSprite.rotate(180);
		break;
	case Compass::West:
		mSprite.rotate(270);
		break;
	default:
		break;
	}

	centerOrigin(mSprite);
}

bool Projectile::isGuided() const
{
	return mType == Missile;
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{

	if (isGuided())
	{
		const float approachRate = 200.f;

		sf::Vector2f newVelocity = unitVector(approachRate * dt.asSeconds() * mTargetDirection + getVelocity());
		newVelocity *= getMaxSpeed();
		float angle = std::atan2(newVelocity.y, newVelocity.x);

		setRotation(toDegree(angle) + 90.f);
		setVelocity(newVelocity);
	}

	Entity::updateCurrent(dt, commands);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Projectile::getCategory() const
{
	if (mType == EnemyBullet)
		return Category::EnemyProjectile;
	else
		return Category::AlliedProjectile;
}

sf::FloatRect Projectile::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

float Projectile::getMaxSpeed() const
{
	return mData.speed;
}

int Projectile::getDamage() const
{
	return mData.damage;
}

void Projectile::updateSprite() {}