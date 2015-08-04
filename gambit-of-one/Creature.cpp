#include "Headers/Creature.hpp"
#include "Headers/DataTables.hpp"
#include <cmath>

namespace
{
	const std::vector<CreatureData> Table = initializeCreatureData();
}

// public methods

Creature::Creature(Type type, const TextureHolder& textures, const FontHolder& fonts)
	: Entity(Table[type].hitpoints)
	, mType(type)
	, mHealthDisplay(nullptr)
	, mArrowDisplay(nullptr)
	, mAttackCountdown(Table[type].attackInterval)
	, mFireCountdown(Table[type].fireInterval)
	, mFireCommand()
	, mDropPickupCommand()
	, mIsFiring(false)
	, mIsAttacking(false)
	, mIsMarkedForRemoval(false)
	, mNormalTexture(textures.get(Table[type].normalTexture))
	, mAttackTexture(textures.get(Table[type].attackTexture))
	, mFiringTexture(textures.get(Table[type].firingTexture))
	, mArrowAmmo(1)
	, mTravelledDistance(0)
	, mDirectionIndex(0)
	, mIsAggroed(false)
{
	mSprite.setTexture(mNormalTexture);
	centerOrigin(mSprite);

	mFireCommand.category = Category::Scene;
	mFireCommand.action = [this, &textures](SceneNode& node, sf::Time)
	{
			createArrows(node, textures);
	};

	mDropPickupCommand.category = Category::Scene;
	mDropPickupCommand.action = [this, &textures](SceneNode& node, sf::Time)
	{
		createPickup(node, textures);
	};

	std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	mHealthDisplay = healthDisplay.get();
	attachChild(std::move(healthDisplay));

	if (getCategory() == Category::Player)
	{
		std::unique_ptr<TextNode> arrowDisplay(new TextNode(fonts, ""));
		arrowDisplay->setPosition(0, 70);
		attachChild(std::move(arrowDisplay));
	}

	updateTexts();
}

unsigned int Creature::getCategory() const
{
	if (isAllied())
		return Category::Player;
	else
		return Category::Enemy;
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

void Creature::collectArrows(unsigned int count)
{
	mArrowAmmo += count;
}

void Creature::attack()
{
	if (isAllied() || !isRanged())
	{
		mIsAttacking = true;
		mSprite.setTexture(mAttackTexture);
		centerOrigin(mSprite);
	}
}

void Creature::fireArrow()
{
	if (isRanged())
	{
		mIsFiring = true;
		mSprite.setTexture(mFiringTexture);
		centerOrigin(mSprite);
	}
}

void Creature::guideTowards(sf::Vector2f position)
{
	assert(isGuided());
	checkAggro(position);
	mTargetDirection = unitVector(position - getWorldPosition());
}


// private methods

void Creature::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Creature::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	// Entity has been destroyed: Possibly drop pickup, mark for removal
	if (isDestroyed())
	{
		checkPickupDrop(commands);

		mIsMarkedForRemoval = true;
		return;
	}

	// Check if there are ranged or melee attacks being done
	checkAttacks(dt, commands);
	checkProjectileLaunch(dt, commands);

	// Update enemy movement pattern; apply velocity
	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);

	// Update texts
	updateTexts();
}

void Creature::updateMovementPattern(sf::Time dt)
{
	// Different AI for different enemies
	// Beast enemies, like rats, converge on the hero.
	// Humanoid enemies have set pathing.
	if (!isGuided()) 
	{
		// Enemy airplane: Movement pattern
		const std::vector<Direction>& directions = Table[mType].directions;
		if (!directions.empty())
		{
			// Moved long enough in current direction: Change direction
			if (mTravelledDistance > directions[mDirectionIndex].distance)
			{
				mDirectionIndex = (mDirectionIndex + 1) % directions.size();
				mTravelledDistance = 0.f;
			}

			float sign = directions[mDirectionIndex].sign;

			// Compute velocity from direction
			float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
			float vx = getMaxSpeed() * std::cos(radians) * sign;
			float vy = getMaxSpeed() * std::sin(radians) * sign;

			setVelocity(vx, vy);

			mTravelledDistance += getMaxSpeed() * dt.asSeconds();
		}
	} 
	else
	{
		if (mIsAggroed)
		{ 
			const float approachRate = 200.f;

			sf::Vector2f newVelocity = unitVector(approachRate
				* dt.asSeconds() * mTargetDirection + getVelocity());

			newVelocity *= getMaxSpeed();
			setVelocity(newVelocity);
		}
	}
}

void Creature::checkPickupDrop(CommandQueue& commands)
{
	if (!isAllied() && randomInt(3) == 0)
		commands.push(mDropPickupCommand);
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

void Creature::checkAttacks(sf::Time dt, CommandQueue& commands)
{
	if (!isAllied())
		attack();

	if (mIsAttacking && mAttackCountdown <= sf::Time::Zero)
	{
		mAttackCountdown += Table[mType].attackInterval;
		mIsAttacking = false;
		mSprite.setTexture(mNormalTexture);
		centerOrigin(mSprite);
	}
	else if (mAttackCountdown > sf::Time::Zero)
	{
		mAttackCountdown -= dt;
		mIsAttacking = false;
	}
}

void Creature::checkProjectileLaunch(sf::Time dt, CommandQueue& commands)
{
	// Only ranged units can fire
	if (!isRanged()) return;

	// Enemies try to fire all the time
	if (!isAllied() && isRanged())
		fireArrow();

	// Check for automatic gunfire, allow only in intervals
	if (mIsFiring && mFireCountdown <= sf::Time::Zero)
	{
		// Interval expired: We can fire a new bullet
		commands.push(mFireCommand);
		mFireCountdown += Table[mType].fireInterval;
		mIsFiring = false;
		mSprite.setTexture(mNormalTexture);
		centerOrigin(mSprite);
	}
	else if (mFireCountdown > sf::Time::Zero)
	{
		// Interval not expired: Decrease it further
		mFireCountdown -= dt;
		mIsFiring = false;
	}
}

void Creature::createArrows(SceneNode& node, const TextureHolder& textures) const
{
	Projectile::Type type = isAllied() ? Projectile::AlliedArrow : Projectile::EnemyArrow;
		
	createProjectile(node, type, 0.0f, 0.5f, textures);
}

void Creature::createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const
{
	std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

	sf::Vector2f offset(xOffset * mSprite.getGlobalBounds().width, yOffset * mSprite.getGlobalBounds().height);
	sf::Vector2f velocity(0, projectile->getMaxSpeed());

	float sign = isAllied() ? -1.f : +1.f;
	projectile->setPosition(getWorldPosition() + offset * sign);
	projectile->setVelocity(velocity * sign);
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
	mHealthDisplay->setString(std::to_string(getHitpoints()) + " HP");
	mHealthDisplay->setPosition(0.f, 50.f);
	mHealthDisplay->setRotation(-getRotation());

	if (mArrowDisplay)
	{
		if (mArrowAmmo == 0)
			mArrowDisplay->setString("");
		else
			mArrowDisplay->setString("M: " + toString(mArrowAmmo));
	}
}