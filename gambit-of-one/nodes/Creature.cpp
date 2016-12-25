/*
Creature.cpp

Date Last Updated: July 4, 2016

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/


#include "Creature.hpp"
#include "BehaviorFactory.h"
#include "DataTables.hpp"
#include "Utility.hpp"
#include "Pickup.hpp"
#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"
#include "CombatBehavior.h"
#include "MovementBehavior.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <random>
#include <ctime>

namespace
{
	BehaviorFactory Factory = BehaviorFactory();
}

using namespace Tables;

Creature::Creature(unsigned int id, const TextureHolder& textures, const FontHolder& fonts)
	: Entity(Creatures[id].constitution * 10)
	, mID(id)
	, mSprite(textures.get(Creatures[id].texture), Creatures[id].textureRect)
	, mIsMarkedForRemoval(false)
	, mDropPickupCommand()
	, mHealthDisplay(nullptr)
	, mTargetDirection()
	, mKillCount(0)
	, mData()
	, mExp(Creatures[id].experience)
{
	mData = Creatures[id];

	BehaviorFactory::CombatStyle combat = static_cast<BehaviorFactory::CombatStyle>(Creatures[id].combatID);
	BehaviorFactory::Movement move = static_cast<BehaviorFactory::Movement>(Creatures[id].movementID);
	mCombatBehavior = Factory.getCombatBehavior(*this, combat);
	mMoveBehavior = Factory.getMovementBehavior(*this, move);
	centerOrigin(mSprite);

	mFireCommand.category = Category::SceneGroundLayer;
	mFireCommand.action = [this, &textures](SceneNode& node, sf::Time)
	{
		createArrow(node, textures);
	};

	mDropPickupCommand.category = Category::SceneGroundLayer;
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

	if (mMoveBehavior->isBlocked())
	{
		mMoveBehavior->unblock();
	}

	// Entity has been destroyed: Possibly drop pickup, mark for removal
	if (isDestroyed())
	{
		checkPickupDrop(commands);

		mIsMarkedForRemoval = true;
		return;
	}

	mCombatBehavior->updateCombatPattern(dt, commands, mTargetPosition);

	// Update enemy movement pattern; apply velocity
	mMoveBehavior->updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);

	// Update texts
	updateTexts();
}

unsigned int Creature::getID() const
{
	return mID;
}

unsigned int Creature::getCategory() const
{
	if (mID == 0)
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
	return mID == 0;
}

bool Creature::isAggroed() const
{
	return mMoveBehavior->isAggroed();
}

bool Creature::isGuided() const
{
	return Creatures[mID].aggroDistance != 0.f;
}

bool Creature::isRanged() const
{
	// Ranged creatures do not have a physical attack, so they do not do melee damage
	BehaviorFactory::CombatStyle combat = static_cast<BehaviorFactory::CombatStyle>(Creatures[mID].combatID);
	return combat == BehaviorFactory::Ranged || combat == BehaviorFactory::Player;
}

bool Creature::isMelee() const
{
	BehaviorFactory::CombatStyle combat = static_cast<BehaviorFactory::CombatStyle>(Creatures[mID].combatID);
	return combat == BehaviorFactory::Melee || combat == BehaviorFactory::Player;
}

bool Creature::isAttacking() const
{
	return mCombatBehavior->isAttacking();
}

bool Creature::isBlocked() const
{
	return mMoveBehavior->isBlocked();
}

float Creature::getMaxSpeed() const
{
	return Creatures[mID].speed;
}

int Creature::getDamage() const
{
	if (isMelee())
	{
		return mCombatBehavior->getDamage(mData.strength, mData.dexterity);
	}
	return 0;
}

float Creature::getAggroDistance() const
{
	return Creatures[mID].aggroDistance;
}

unsigned int Creature::getAction() const
{
	return mCombatBehavior->getAction();
}

void Creature::block()
{
	// Path of the Creature is stopped
	mMoveBehavior->block();
}

void Creature::fire(CommandQueue& commands)
{
	commands.push(mFireCommand);
}

void Creature::setAction(Player::Action action)
{
	mCombatBehavior->setAction(action);
}

void Creature::attack() 
{
	mCombatBehavior->attack();
}

void Creature::checkPickupDrop(CommandQueue& commands)
{
	if (!isAllied() && randomInt(3) == 0)
		commands.push(mDropPickupCommand);
}

void Creature::incrementKillCount()
{
	mKillCount += 1;
}

int Creature::getKillCount()
{
	return mKillCount;
}

CreatureData Creature::getData() const
{
	return mData;
}

int Creature::getMaxHitpoints() const
{
	return mMaxHitpoints;
}

void Creature::updateData(CreatureData stats)
{
	mData.constitution = stats.constitution;
	mData.strength = stats.strength;
	mData.dexterity = stats.dexterity;
	mData.intelligence = stats.intelligence;
	mData.charisma = stats.charisma;
	mCombatBehavior->setStats();
	
	if (Entity::getMaxHitpoints() < stats.constitution * 10)
	{
		Entity::setHitpoints(stats.constitution * 10);
	}
}

void Creature::checkAggro(sf::Vector2f position)
{
	mMoveBehavior->checkAggro();
}

int Creature::getExp() const
{
	if (mID == 0)
	{
		return mExp;
	}
	return Creatures[mID].experience;
}


void Creature::setExp(int amount)
{
	mExp = amount;
}

void Creature::incExp(int amount)
{
	mExp += amount;
}

void Creature::createPickup(SceneNode& node, const TextureHolder& textures) const
{
	// Not increasing archery stats at the time
	//auto type = static_cast<Pickup::Type>(randomInt(Pickup::TypeCount));

	std::unique_ptr<Pickup> pickup(new Pickup(Pickup::HealthRefill, textures));
	pickup->setPosition(getWorldPosition());
	pickup->setVelocity(0.f, 1.f);
	node.attachChild(std::move(pickup));
}

void Creature::createArrow(SceneNode& node, const TextureHolder& textures)
{
	auto& creature = static_cast<Creature&>(node);
	sf::FloatRect bounds = mSprite.getGlobalBounds();
	Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;
	std::unique_ptr<Projectile> projectile(new Projectile(type, textures, getCompass()));
	projectile->setStats(mData.dexterity, mData.strength);

	sf::Vector2f velocity;
	sf::Vector2f offset(0, 0);
	float angle = atan2(getVelocity().y, getVelocity().x);
	switch (getCompass())
	{
	case Compass::North:
		velocity.x = 0;
		velocity.y = projectile->getMaxSpeed() * -1.f;
		offset.y = 0.5f * bounds.height;
		break;
	case Compass::South:
		velocity.x = 0;
		velocity.y = projectile->getMaxSpeed();
		offset.y = -0.5f * bounds.height;
		break;
	case Compass::East:
		velocity.x = projectile->getMaxSpeed();
		velocity.y = 0;
		offset.x = 0.5f * bounds.width;
		break;
	case Compass::West:
		velocity.x = projectile->getMaxSpeed() * - 1.f;
		velocity.y = 0;
		offset.x = -0.5f * bounds.width;
		break;
	}

	if (getVelocity().x < 0)
	{
		velocity.x = getVelocity().x - (projectile->getMaxSpeed() * cos(angle));
	}
	else if (getVelocity().x > 0)
	{
		velocity.x = getVelocity().x + (projectile->getMaxSpeed() * cos(angle));
	}
	if (getVelocity().y < 0)
	{
		velocity.y = getVelocity().y - (projectile->getMaxSpeed() * sin(angle));
	}
	else if (getVelocity().y > 0)
	{
		velocity.y = getVelocity().y + (projectile->getMaxSpeed() * sin(angle));
	}

	projectile->setRotation(angle);
	projectile->setPosition(getWorldPosition() + offset);
	projectile->setVelocity(velocity);
	node.attachChild(std::move(projectile));
}

void Creature::updateTexts()
{
	mHealthDisplay->setString(toString(getHitpoints()) + " HP");
	mHealthDisplay->setPosition(0.f, 50.f);
	mHealthDisplay->setRotation(-getRotation());
}

Compass Creature::getCompass() const
{
	return mMoveBehavior->getCompass();
}

void Creature::updateSprite()
{
	sf::IntRect textureRect = mSprite.getTextureRect();
	textureRect.top = 0;
	textureRect.left = 0;

	mMoveBehavior->checkCompass();
	switch (getCompass())
	{
	case Compass::South:
		textureRect.left = 0;
		break;
	case Compass::East:
		textureRect.left += textureRect.width;
		break;
	case Compass::North:
		textureRect.left += 2 * textureRect.width;
		break;
	case Compass::West:
		textureRect.left += 3 * textureRect.width;
		break;
	}

	if (mCombatBehavior->isAttacking())
		textureRect.top += mCombatBehavior->getTileMultiplier() * textureRect.height;

	mSprite.setTextureRect(textureRect);
}

void Creature::guideTowards(sf::Vector2f position)
{
	mMoveBehavior->guide(position);
}