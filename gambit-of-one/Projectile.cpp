#include "Headers/Projectile.h"

namespace
{
	const std::vector<ProjectileData> ProjectileTable = initializeProjectileData();
}

// public
Projectile::Projectile(Type type, const TextureHolder& textures)
	: Entity(1)
	, mType(type)
	, mSprite(textures.get(ProjectileTable[type].texture))
	, mTargetDirection()
{
	centerOrigin(mSprite);
}

bool Projectile::isGuided() const
{
	return false;
}

void Projectile::guideTowards(sf::Vector2f position)
{
	assert(isGuided());
	mTargetDirection = unitVector(position - getWorldPosition());
}

unsigned int Projectile::getCategory() const
{
	if (mType == EnemyArrow)
	{
		return Category::EnemyProjectile;
	}
	else
	{
		return Category::AlliedProjectile;
	}
}

sf::FloatRect Projectile::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

float Projectile::getMaxSpeed() const
{
	return ProjectileTable[mType].speed;
}

int Projectile::getDamage() const
{
	return ProjectileTable[mType].damage;
}

// private
void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (isGuided())
	{
		const float approachRate = 200.f;

		sf::Vector2f newVelocity = unitVector(approachRate
			* dt.asSeconds() * mTargetDirection + getVelocity());

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

