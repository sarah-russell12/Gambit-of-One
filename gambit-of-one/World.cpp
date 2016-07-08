/*
World.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/

#include "World.hpp"
#include "Projectile.hpp"
#include "Pickup.hpp"
#include "Foreach.hpp"
#include "TextNode.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>
#include <limits>

World::World(sf::RenderWindow& window, FontHolder& fonts)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mFonts(fonts)
	, mTextures()
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(0.f, 0.f, 2750.f, mWorldView.getSize().y)
	, mSpawnPosition(mWorldBounds.left + mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f)
	, mScrollSpeed(0.f)
	, mPlayerCreature(nullptr)
	, mEnemySpawnPoints()
	, mScenerySpawnPoints()
	, mActiveEnemies()
	, mActiveScenery()
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{

	sf::Vector2f velocity = mPlayerCreature->getVelocity();

	if (!mPlayerCreature->isBlocked())
	{
		mWorldView.move(velocity.x * dt.asSeconds(), 0.f);
	}
	mWorldView.setCenter(mPlayerCreature->getPosition().x, mSpawnPosition.y);
	mPlayerCreature->setVelocity(0.f, 0.f);

	guideCreatures();

	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	adaptPlayerVelocity();

	handleCollisions();

	mSceneGraph.removeWrecks();
	spawnEnemies();
	spawnScenery();

	mSceneGraph.update(dt, mCommandQueue);
	adaptPlayerPosition();
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

bool World::hasAlivePlayer() const
{
	return !mPlayerCreature->isMarkedForRemoval();
}

bool World::hasPlayerReachedEnd() const
{
	return !mWorldBounds.contains(mPlayerCreature->getPosition());
}

void World::loadTextures()
{
	mTextures.load(Textures::Hero, "Media/Textures/HeroSpriteSheet.png");
	mTextures.load(Textures::Rat, "Media/Textures/RatSpriteSheet.png");
	mTextures.load(Textures::Archer, "Media/Textures/ArcherSpriteSheet.png");
	mTextures.load(Textures::Bandit, "Media/Textures/BanditSpriteSheet.png");

	mTextures.load(Textures::Road, "Media/Textures/DirtRoad.png");
	mTextures.load(Textures::Arrow, "Media/Textures/Arrow.png");

	mTextures.load(Textures::HealthRefill, "Media/Textures/HealthPotion.png");
	//mTextures.load(Textures::MissileRefill, "Media/Textures/Quiver.png");
	mTextures.load(Textures::FireSpread, "Media/Textures/FireSpread.png");
	mTextures.load(Textures::FireRate, "Media/Textures/FireRate.png");

	mTextures.load(Textures::Rock, "Media/Textures/Rock.png");
}

void World::adaptPlayerPosition()
{
	sf::FloatRect viewBounds = getViewBounds();
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerCreature->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerCreature->setPosition(position);
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayerCreature->getVelocity();

	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerCreature->setVelocity(velocity / std::sqrt(2.f));

	mPlayerCreature->accelerate(0.f, mScrollSpeed);
}

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

	FOREACH(SceneNode::Pair pair, collisionPairs)
	{
		if (matchesCategories(pair, Category::PlayerCreature, Category::EnemyCreature))
		{
			auto& player = static_cast<PlayerCreature&>(*pair.first);
			auto& enemy = static_cast<Creature&>(*pair.second);

			if (player.isAttacking(Player::Attack) && !enemy.isImmune())
			{
				enemy.damage(player.getDamage());
				return;
			}
			if (!player.isAttacking(Player::Attack) && !player.isImmune() && enemy.isAttacking())
			{
				player.damage(enemy.getDamage());
				return;
			}
		}

		else if (matchesCategories(pair, Category::PlayerCreature, Category::Pickup))
		{
			auto& player = static_cast<Creature&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);

			pickup.apply(player);
			pickup.destroy();
			return;
		}

		else if (matchesCategories(pair, Category::EnemyCreature, Category::AlliedProjectile)
			|| matchesCategories(pair, Category::PlayerCreature, Category::EnemyProjectile))
		{
			auto& creature = static_cast<Creature&>(*pair.first);
			auto& projectile = static_cast<Projectile&>(*pair.second);

			creature.damage(projectile.getDamage());
			projectile.destroy();
		}
		else if (matchesCategories(pair, Category::Creature, Category::Scenery))
		{
			handleSceneryCollison(pair);
		}
		else if (matchesCategories(pair, Category::Projectile, Category::Scenery))
		{
			// Destroy the projectile upon hitting the Scenery blocking it

			auto& projectile = static_cast<Projectile&>(*pair.first);

			projectile.destroy();
		}
	}
}

void World::handleSceneryCollison(SceneNode::Pair pair)
{
	auto& creature = static_cast<Creature&>(*pair.first);
	auto& scenery = static_cast<Scenery&>(*pair.second);

	// Variables simplify the look of the conditions
	sf::FloatRect creatBounds = creature.getBoundingRect();
	float creatBottom = creatBounds.top + creatBounds.height;
	float creatRight = creatBounds.left + creatBounds.width;
	sf::Vector2f creatPos = creature.getPosition();

	sf::FloatRect propBounds = scenery.getBoundingRect();
	float propBottom = propBounds.top + propBounds.height;
	float propRight = propBounds.left + propBounds.width;
	sf::Vector2f propPos = scenery.getPosition();

	float margin = 2.f;

	// New position of the creature
	sf::Vector2f pos;

	creature.block();


	if ((creatBounds.top < propBottom) && (creatPos.y > propPos.y))
	{
		// If a creature is moving up, it will collide halfway with any scenery.
		// Kind of looks like it is walking up to the scenery item.
		if (propBounds.contains(creatPos))
		{
			// Movement should be unrestricted until the center (the position/origin)
			// of the creature intersects the scenery
			pos.x = creatPos.x;
			pos.y = propBottom + margin;
			creature.setPosition(pos);
		}
		return;
	}
	if (creatPos.y < propBottom && creatPos.y > propBounds.top)
	{
		// the creature is colliding from the prop's left or right
		pos.y = creatPos.y;
		if (creatRight > propBounds.left && !(creatPos.x > propBounds.left))
		{
			// Collision from the prop's left
			pos.x = propBounds.left - margin - (creatBounds.width / 2.f);
		}
		else
		{
			pos.x = propRight + margin + (creatBounds.width / 2.f);
		}
		creature.setPosition(pos);
		return;
	}
	if (creatBottom > propBounds.top)
	{
		pos.x = creatPos.x;
		pos.y = propBounds.top - margin - (creatBounds.height / 2.f);
		creature.setPosition(pos);
		return;
	}
}

void World::buildScene()
{
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		Category::Type category = (i == Ground) 
			? Category::SceneGroundLayer : Category::None;

		SceneNode::Ptr layer(new SceneNode(category));
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	sf::Texture& texture = mTextures.get(Textures::Road);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	std::unique_ptr<PlayerCreature> player(new PlayerCreature(Creature::Hero, mTextures, mFonts));
	mPlayerCreature = player.get();
	mPlayerCreature->setPosition(mSpawnPosition);
	mSceneLayers[Ground]->attachChild(std::move(player));

	addScenery();
	addEnemies();
	sortSpawnPoints();
}

void World::addEnemies()
{
	addEnemy(Creature::Rat, 750.f, -175.f);
	addEnemy(Creature::Rat, 1200.f, 100.f);
	addEnemy(Creature::Archer, 1100.f, -200.f);
	addEnemy(Creature::Rat, 1400.f, -250.f);
	//addEnemy(Creature::Archer, -400.f, 1500.f);
	addEnemy(Creature::Rat, 1400.f, 200.f);
	addEnemy(Creature::Bandit, 1600.f, -100.f);
	addEnemy(Creature::Rat, 500.f, 0.f);

}

void World::addScenery()
{

	// Test player unable to move against rock
	addSceneryItem(Scenery::Rock, 300.f, 0.f);

	// Test collision with enemy projectiles by placing rock next to archer
	addSceneryItem(Scenery::Rock, 900.f, -200.f);
}

void World::addEnemy(Creature::Type type, float relX, float relY)
{
	SpawnPoint spawn(type, mSpawnPosition.x + relX, mSpawnPosition.y - relY);
	mEnemySpawnPoints.push_back(spawn);
}

void World::addSceneryItem(Scenery::Type type, float relX, float relY)
{
	ScenerySpawn spawn(type, mSpawnPosition.x + relX, mSpawnPosition.y - relY);
	mScenerySpawnPoints.push_back(spawn);
}

void World::spawnEnemies()
{
	while (!mEnemySpawnPoints.empty()
		&& mEnemySpawnPoints.back().x > getBattlefieldBounds().width)
	{
		SpawnPoint spawn = mEnemySpawnPoints.back();

		std::unique_ptr<Creature> enemy(new Creature(spawn.type, mTextures, mFonts));
		enemy->setPosition(spawn.x, spawn.y);

		mSceneLayers[Ground]->attachChild(std::move(enemy));

		mEnemySpawnPoints.pop_back();
	}
}

void World::spawnScenery()
{
	while (!mScenerySpawnPoints.empty() 
		&& mScenerySpawnPoints.back().x > getBattlefieldBounds().left)
	{
		ScenerySpawn spawn = mScenerySpawnPoints.back();
		
		std::unique_ptr<Scenery> scenery(new Scenery(spawn.type, mTextures));
		scenery->setPosition(spawn.x, spawn.y);

		mSceneLayers[Objects]->attachChild(std::move(scenery));

		mScenerySpawnPoints.pop_back();
	}
}

void World::destroyEntitiesOutsideView()
{
	Command command;
	command.category = Category::Projectile | Category::EnemyCreature;
	command.action = derivedAction<Entity>([this](Entity& e, sf::Time)
	{
		if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
			if (e.getCategory() == Category::Scenery) 
			{
				// We don't want the scenery to be destroyed so we add it back
				// into the spawn points
				auto& scenery = static_cast<Scenery&>(e);
				sf::Vector2f pos = scenery.getPosition();
				ScenerySpawn spawn(scenery.getType(), pos.x, pos.y);
				mScenerySpawnPoints.push_back(spawn);
				sortSpawnPoints();
			}
			e.destroy();
	});

	mCommandQueue.push(command);
}

void World::guideCreatures()
{
	Command enemyCollector;
	enemyCollector.category = Category::EnemyCreature;
	enemyCollector.action = derivedAction<Creature>([this](Creature& enemy, sf::Time)
	{
		if (!enemy.isDestroyed())
			mActiveEnemies.push_back(&enemy);
	});
	
	Command creatureGuider;
	creatureGuider.category = Category::EnemyCreature;
	creatureGuider.action = derivedAction<Creature>([this](Creature& creature, sf::Time)
	{
		if (!creature.isGuided())
			return;

		sf::Vector2f playerPosition = mPlayerCreature->getWorldPosition();
		FOREACH(Creature* enemy, mActiveEnemies)
		{
			//enemy->checkAggro(playerPosition);
			//if (enemy->isAggroed() && enemy->isGuided())
				enemy->guideTowards(playerPosition);
		}	
	});

	mCommandQueue.push(enemyCollector);
	mCommandQueue.push(creatureGuider);
	mActiveEnemies.clear();
}

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const
{
	sf::FloatRect bounds = getViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;
	bounds.left -= 100.f;
	bounds.width += 100.f;

	return bounds;
}

void World::sortSpawnPoints()
{
	std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(), [](SpawnPoint lhs, SpawnPoint rhs)
	{
		return lhs.x < rhs.x;
	});

	std::sort(mScenerySpawnPoints.begin(), mScenerySpawnPoints.end(), [](ScenerySpawn lhs, ScenerySpawn rhs)
	{
		return lhs.x < rhs.x;
	});
}