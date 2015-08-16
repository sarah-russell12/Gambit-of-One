#include "Projectile.hpp"
#include "DataTables.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <cassert>


namespace
{
	const std::vector<ProjectileData> Table = initializeProjectileData();
}

Projectile::Projectile(Type type, const TextureHolder& textures, const Entity::cDirection& direction)
	: Entity(1)
	, mType(type)
	, mSprite(textures.get(Table[type].texture))
	, mTargetDirection()
	, mCDirection(direction)
	, upArrow()
	, downArrow()
	, leftArrow()
	, rightArrow()
{
	switch (direction)
	{
	case North:
		break;
	case East:
		rotate(90);
		break;
	case South:
		rotate(180);
		break;
	case West:
		rotate(270);
		break;
	default:
		break;
	}

	centerOrigin(mSprite);
}

//void Projectile::guideTowards(sf::Vector2f position)
//{
//	assert(isGuided());
//	mTargetDirection = unitVector(position - getWorldPosition());
//}

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
	return Table[mType].speed;
}

int Projectile::getDamage() const
{
	return Table[mType].damage;
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