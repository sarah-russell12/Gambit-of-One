#include "Projectile.h"
#include "Entities_Facilities.h"
#include "Centering.h"

#include <cmath>
#include <assert.h>

Projectile::Projectile(Type type, const TextureHolder& textures)
	: Entity(1)
	, mType(type)
	, mSprite(textures.get(ProjectileTable[type].texture))
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

