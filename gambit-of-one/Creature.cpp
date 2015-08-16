/*
Creature.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/


#include "Creature.hpp"
#include "DataTables.hpp"
#include "Utility.hpp"
#include "Pickup.hpp"
#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>

namespace
{
	const std::vector<CreatureData> Table = initializeCreatureData();
}

Creature::Creature(Type type, const TextureHolder& textures, const FontHolder& fonts)
	: Entity(Table[type].hitpoints)
	, mType(type)
	, mSprite(textures.get(Table[type].texture), Table[type].textureRect)
	, mFireCommand()
	, mAttackCountdown(sf::Time::Zero)
	, mFireCountdown(sf::Time::Zero)
	, mIsFiring(false)
	, mIsAttacking(false)
	, mIsMarkedForRemoval(false)
	, mFireRateLevel(1)
	, mSpreadLevel(1)
	, mDropPickupCommand()
	, mTravelledDistance(0.f)
	, mDirectionIndex(0)
	, mHealthDisplay(nullptr)
	, mHeroTextures()
	, mCompass(South)
	, mIsAggroed(false)
	, mTargetDirection()
		
{

	centerOrigin(mSprite);

	mFireCommand.category = Category::SceneAirLayer;
	mFireCommand.action = [this, &textures](SceneNode& node, sf::Time)
	{
		createArrows(node, textures);
	};

	mDropPickupCommand.category = Category::SceneAirLayer;
	mDropPickupCommand.action = [this, &textures](SceneNode& node, sf::Time)
	{
		createPickup(node, textures);
	};

	std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	mHealthDisplay = healthDisplay.get();
	attachChild(std::move(healthDisplay));

	updateTexts();
}

void Creature::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Creature::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	updateSprite();
	// Entity has been destroyed: Possibly drop pickup, mark for removal
	if (isDestroyed())
	{
		checkPickupDrop(commands);

		mIsMarkedForRemoval = true;
		return;
	}

	checkProjectileLaunch(dt, commands);

	checkAttacks(dt, commands);


	// Update enemy movement pattern; apply velocity
	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);

	// Update texts
	updateTexts();
}

unsigned int Creature::getCategory() const
{
	if (isAllied())
		return Category::PlayerCreature;
	else
		return Category::EnemyCreature;
}

sf::FloatRect Creature::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Creature::isMarkedForRemoval() const
{
	return mIsMarkedForRemoval;
}

bool Creature::isAllied() const
{
	return mType == Hero;
}

bool Creature::isAggroed() const
{
	return mIsAggroed;
}

bool Creature::isGuided() const
{
	return Table[mType].aggroDistance != 0.f;
}

bool Creature::isRanged() const
{
	return Table[mType].fireInterval != sf::Time::Zero;
}

bool Creature::isMelee() const
{
	return Table[mType].attackInterval != sf::Time::Zero;
}

bool Creature::isAttacking() const
{
	return mIsAttacking;
}

float Creature::getMaxSpeed() const
{
	return Table[mType].speed;
}

int Creature::getDamage() const
{
	return Table[mType].attackDamage;
}

float Creature::getAggroDistance() const
{
	return Table[mType].aggroDistance;
}

void Creature::increaseFireRate()
{
	if (mFireRateLevel < 10)
		++mFireRateLevel;
}

void Creature::increaseSpread()
{
	if (mSpreadLevel < 3)
		++mSpreadLevel;
}

void Creature::fire()
{
	if (Table[mType].fireInterval != sf::Time::Zero)
		mIsFiring = true;
}

void Creature::attack()
{
	if (Table[mType].attackInterval != sf::Time::Zero)
		mIsAttacking = true;
}

void Creature::updateMovementPattern(sf::Time dt)
{
	if (isGuided() && mIsAggroed)
	{
		const float approachRate = getMaxSpeed();

		sf::Vector2f newVelocity = unitVector(approachRate * dt.asSeconds() * mTargetDirection + getVelocity());
		newVelocity *= getMaxSpeed();
		
		setVelocity(newVelocity);
	}

	if (isRanged() && mIsAggroed)
	{
		sf::Vector2f currentDirection = mTargetDirection;

		if (abs(currentDirection.x) > abs(currentDirection.y))
		{
			if (currentDirection.x > 0)
				mCompass = East;
			else
				mCompass = West;
		}
		else if (!(currentDirection.x == 0 && currentDirection.y == 0))
		{
			if (currentDirection.y > 0)
				mCompass = South;
			else
				mCompass = North;
		}
	}
}

void Creature::checkPickupDrop(CommandQueue& commands)
{
	if (!isAllied() && randomInt(3) == 0)
		commands.push(mDropPickupCommand);
}

void Creature::checkProjectileLaunch(sf::Time dt, CommandQueue& commands)
{
	// Enemies try to fire all the time
	if (!isAllied())
		fire();

	// Check for automatic gunfire, allow only in intervals
	if (mIsFiring && mFireCountdown <= sf::Time::Zero)
	{
		// Interval expired: We can fire a new bullet
		commands.push(mFireCommand);
		mFireCountdown += Table[mType].fireInterval / (mFireRateLevel + 1.f);
		mIsFiring = false; 
		// update Sprite
	}
	else if (mFireCountdown > sf::Time::Zero)
	{
		// Interval not expired: Decrease it further
		mFireCountdown -= dt;
		mIsFiring = false;
	}
}

void Creature::checkAttacks(sf::Time dt, CommandQueue& commands)
{
	if (mIsAttacking && mAttackCountdown <= sf::Time::Zero)
	{
		mAttackCountdown += Table[mType].attackInterval;
		mIsAttacking = false;
	}
	else if (mAttackCountdown > sf::Time::Zero)
	{
		mAttackCountdown -= dt;
		mIsAttacking = false;
	}
}

void Creature::checkAggro(sf::Vector2f position)
{
	if (!isGuided())
		return;

	sf::Vector2f thisPosition = getPosition();
	if (length(thisPosition - position) < Table[mType].aggroDistance)
		mIsAggroed = true;
	else
		mIsAggroed = false;
}

void Creature::createArrows(SceneNode& node, const TextureHolder& textures) const
{
	Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;

	switch (mSpreadLevel)
	{
	case 1:
		createProjectile(node, type, 0.0f, 0.5f, textures);
		break;

	case 2:
		createProjectile(node, type, -0.33f, 0.33f, textures);
		createProjectile(node, type, +0.33f, 0.33f, textures);
		break;

	case 3:
		createProjectile(node, type, -0.5f, 0.33f, textures);
		createProjectile(node, type, 0.0f, 0.5f, textures);
		createProjectile(node, type, +0.5f, 0.33f, textures);
		break;
	}
}

void Creature::createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const
{
	std::unique_ptr<Projectile> projectile(new Projectile(type, textures, mCompass));

	//sf::Vector2f offset(xOffset * mSprite.getGlobalBounds().width, yOffset * mSprite.getGlobalBounds().height);
	
	/*sf::Vector2f velocity(0, projectile->getMaxSpeed());
	float sign = isAllied() ? -1.f : +1.f;*/
	sf::Vector2f velocity;
	float sign;

	switch (mCompass)
	{
	case North:
		velocity.x = 0;
		velocity.y = projectile->getMaxSpeed() * -1.f;
		break;
	case South:
		velocity.x = 0;
		velocity.y = projectile->getMaxSpeed();
		break;
	case East:
		velocity.x = projectile->getMaxSpeed();
		velocity.y = 0;
		break;
	case West:
		velocity.x = projectile->getMaxSpeed() * -1.f;
		velocity.y = 0;
		break;
	}
	
	projectile->setPosition(getWorldPosition());
	projectile->setVelocity(velocity);
	node.attachChild(std::move(projectile));
}

void Creature::createPickup(SceneNode& node, const TextureHolder& textures) const
{
	auto type = static_cast<Pickup::Type>(randomInt(Pickup::TypeCount));

	std::unique_ptr<Pickup> pickup(new Pickup(type, textures));
	pickup->setPosition(getWorldPosition());
	pickup->setVelocity(0.f, 1.f);
	node.attachChild(std::move(pickup));
}

void Creature::updateTexts()
{
	mHealthDisplay->setString(toString(getHitpoints()) + " HP");
	mHealthDisplay->setPosition(0.f, 50.f);
	mHealthDisplay->setRotation(-getRotation());
}

Entity::cDirection Creature::getCompass() const
{
	return mCompass;
}

void Creature::updateCompass()
{
	sf::Vector2f velocity = getVelocity();
	if (abs(velocity.x) > abs(velocity.y))
	{
		if (velocity.x > 0)
			mCompass = East;
		else
			mCompass = West;
	}
	else if (!(velocity.x == 0 && velocity.y == 0))
	{
		if (velocity.y > 0)
			mCompass = South;
		else
			mCompass = North;
	}
}

void Creature::updateCreatureDirection()
{
	sf::IntRect textureRect = mSprite.getTextureRect();
	textureRect.left = 0;
	updateCompass();
	switch (mCompass)
	{
	case North:
		textureRect.left += 2 * textureRect.width;
		break;
	case South:
		textureRect.left = 0;
		break;
	case East:
		textureRect.left += textureRect.width;
		break;
	case West:
		textureRect.left += 3 * textureRect.width;
		break;
	}
	mSprite.setTextureRect(textureRect);
}

void Creature::updateSprite()
{
	updateCreatureDirection();
	sf::IntRect textureRect = mSprite.getTextureRect();
	textureRect.top = 0;

	if (mIsFiring || mFireCountdown > sf::Time::Zero)
		textureRect.top += textureRect.height;
	if (mIsAttacking || mAttackCountdown > sf::Time::Zero)
		textureRect.top += 2 * textureRect.height;
	mSprite.setTextureRect(textureRect);
}

void Creature::guideTowards(sf::Vector2f position)
{
	assert(isGuided());
	mTargetDirection = unitVector(position - getWorldPosition());
}