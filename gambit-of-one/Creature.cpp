#include "Headers/Creature.hpp"
#include "Headers/DataTables.hpp"
#include <cmath>

namespace
{
	const std::vector<CreatureData> Table = initializeCreatureData();
}

Creature::Creature(Type type, const TextureHolder& textures, const FontHolder& fonts)
	: Entity(Table[type].hitpoints)
	, mType(type)
	, mDamage(Table[type].damage)
	, mSprite(textures.get(Table[type].texture))
	, mFireCommand()
	, mFireCountdown(sf::Time::Zero)
	, mIsAttacking(false)
	, mIsMarkedForRemoval(false)
	, mDropPickupCommand()
	, mTravelledDistance(0.f)
	, mDirectionIndex(0)
	, mHealthDisplay(nullptr)
	, mArrowDisplay(nullptr)
{
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

	std::unique_ptr<TextNode> arrowDisplay(new TextNode(fonts, ""));
	mHealthDisplay = arrowDisplay.get();
	attachChild(std::move(arrowDisplay));

	if (getCategory() == Category::Player)
	{
		std::unique_ptr<TextNode> arrowDisplay(new TextNode(fonts, ""));
		arrowDisplay->setPosition(0, 70);
		attachChild(std::move(arrowDisplay));
	}

	updateTexts();
}

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

	// Check if bullets or missiles are fired
	checkProjectileLaunch(dt, commands);

	// Update enemy movement pattern; apply velocity
	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);

	// Update texts
	updateTexts();
}

unsigned int Creature::getCategory() const
{
	if (isAllied())
		return Category::Player;
	else
		return Category::Enemy;
}

int Creature::getDamage()
{
	return mDamage;
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

bool Creature::isRanged() const
{
	return (mType == Hero || mType == Archer);
}

bool Creature::isGuided() const
{
	return (mType == Rat);
}

bool Creature::isAttacking() 
{
	return mIsAttacking;
}

float Creature::getMaxSpeed() const
{
	return Table[mType].speed;
}

void Creature::collectArrows(unsigned int count)
{
	mArrowCount += count;
}

void Creature::fireArrow()
{
	if (mArrowCount > 0)
	{
		mIsFiring = true;
		--mArrowCount;
	}
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

			// Compute velocity from direction
			float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
			float vx = getMaxSpeed() * std::cos(radians);
			float vy = getMaxSpeed() * std::sin(radians);

			setVelocity(vx, vy);

			mTravelledDistance += getMaxSpeed() * dt.asSeconds();
		}
	} 
	else
	{
		const float approachRate = 200.f;

		sf::Vector2f newVelocity = unitVector(approachRate
			* dt.asSeconds() * mTargetDirection + getVelocity());

		newVelocity *= getMaxSpeed();
		float angle = std::atan2(newVelocity.y, newVelocity.x);

		setRotation(toDegree(angle) + 90.f);
		setVelocity(newVelocity);
	}
}

void Creature::guideTowards(sf::Vector2f position)
{
	assert(mIsGuidedEnemy);
	mTargetDirection = unitVector(position - getWorldPosition());
}

void Creature::checkPickupDrop(CommandQueue& commands)
{
	if (!isAllied() && randomInt(3) == 0)
		commands.push(mDropPickupCommand);
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
		if (mArrowCount == 0)
			mArrowDisplay->setString("");
		else
			mArrowDisplay->setString("M: " + std::to_string(mArrowCount));
	}
}