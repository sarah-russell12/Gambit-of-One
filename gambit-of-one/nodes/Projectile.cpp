/*
Projectile.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/

#include "Projectile.hpp"
#include "DataTables.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <cassert>
#include <random>
#include <ctime>


using namespace Tables;

Projectile::Projectile(Type type, const TextureHolder& textures, const Compass& direction)
	: Entity(1)
	, mType(type)
	, mSprite(textures.get(Projectiles[type].texture))
	, mTargetDirection()
	, mCDirection(direction)
	, mMain(0)
	, mLimiter(0)
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

void Projectile::guideTowards(sf::Vector2f position)
{
	assert(isGuided());
	mTargetDirection = unitVector(position - getWorldPosition());
}

bool Projectile::isGuided() const
{
	return mType == Magic;
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
	return mMain * 20.f;		// A poor marksman or magician should not have fast projectiles
}

int Projectile::getDamage() const
{
	std::default_random_engine generator(time(0));
	std::uniform_int_distribution<int> dist6(1, 6);
	std::uniform_int_distribution<int> dist4(1, 4);
	auto roll_d6 = std::bind(dist6, generator);
	auto roll_d4 = std::bind(dist4, generator);

	int damage = 0;
	for (int i = 0; i < mMain; i++)
	{
		damage += roll_d6();
	}
	// If dexterity is too low, then your damage output is less
	if (mLimiter < (0.5f * mMain))
	{
		int diff = int((0.5f * mMain - mLimiter) + 1);
		for (int j = 0; j < diff; j++)
		{
			damage -= roll_d4();
		}
	}
	return damage;
}

void Projectile::updateSprite()
{
	//switch (mCDirection)
	//{
	//case North:
	//	rot
	//case East:
	//	mSprite = rightArrow;
	//case South:
	//	mSprite = downArrow;
	//case West:
	//	mSprite = leftArrow;
	//default:
	//	break;
	//}
}

void Projectile::setStats(unsigned int main, unsigned int limiter)
{
	mMain = main;
	mLimiter = limiter;
}