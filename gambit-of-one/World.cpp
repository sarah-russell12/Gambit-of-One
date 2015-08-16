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
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
	, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
	, mScrollSpeed(0.f)
	, mPlayerCreature(nullptr)
	, mEnemySpawnPoints()
	, mActiveEnemies()
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{

	sf::Vector2f velocity = mPlayerCreature->getVelocity();

	mWorldView.move(velocity.x * dt.asSeconds(), velocity.y * dt.asSeconds());
	mPlayerCreature->setVelocity(0.f, 0.f);

	guideCreatures();

	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	adaptPlayerVelocity();

	handleCollisions();

	mSceneGraph.removeWrecks();
	spawnEnemies();

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
	mTextures.load(Textures::MissileRefill, "Media/Textures/Quiver.png");
	mTextures.load(Textures::FireSpread, "Media/Textures/FireSpread.png");
	mTextures.load(Textures::FireRate, "Media/Textures/FireRate.png");
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
			auto& player = static_cast<Creature&>(*pair.first);
			auto& enemy = static_cast<Creature&>(*pair.second);

			if (player.isAttacking() && !enemy.isImmune())
				enemy.damage(player.getDamage());
			
			if (!player.isImmune() && !player.isAttacking() && enemy.isAttacking())
			{
				player.damage(enemy.getDamage());
			}
			//enemy.destroy();
		}

		else if (matchesCategories(pair, Category::PlayerCreature, Category::Pickup))
		{
			auto& player = static_cast<Creature&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);

			pickup.apply(player);
			pickup.destroy();
		}

		else if (matchesCategories(pair, Category::EnemyCreature, Category::AlliedProjectile)
			|| matchesCategories(pair, Category::PlayerCreature, Category::EnemyProjectile))
		{
			auto& aircraft = static_cast<Creature&>(*pair.first);
			auto& projectile = static_cast<Projectile&>(*pair.second);

			aircraft.damage(projectile.getDamage());
			projectile.destroy();
		}
	}
}

void World::buildScene()
{
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		Category::Type category = (i == Air) ? Category::SceneAirLayer : Category::None;

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

	std::unique_ptr<Creature> player(new Creature(Creature::Hero, mTextures, mFonts));
	mPlayerCreature = player.get();
	mPlayerCreature->setPosition(mSpawnPosition);
	mSceneLayers[Air]->attachChild(std::move(player));

	addEnemies();
}

void World::addEnemies()
{
	addEnemy(Creature::Bandit, -350.f, 750.f);
	addEnemy(Creature::Rat, +100.f, 1200.f);
	//addEnemy(Creature::Archer, -400.f, 1100.f);
	addEnemy(Creature::Rat, -70.f, 1400.f);
	//addEnemy(Creature::Archer, -400.f, 1500.f);
	addEnemy(Creature::Rat, 400.f, 1400.f);
	addEnemy(Creature::Bandit, -200.f, 1600.f);
	addEnemy(Creature::Rat, 0.f, 500.f);

	std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(), [](SpawnPoint lhs, SpawnPoint rhs)
	{
		return lhs.y < rhs.y;
	});
}

void World::addEnemy(Creature::Type type, float relX, float relY)
{
	SpawnPoint spawn(type, mSpawnPosition.x + relX, mSpawnPosition.y - relY);
	mEnemySpawnPoints.push_back(spawn);
}

void World::spawnEnemies()
{
	while (!mEnemySpawnPoints.empty()
		&& mEnemySpawnPoints.back().y > getBattlefieldBounds().top)
	{
		SpawnPoint spawn = mEnemySpawnPoints.back();

		std::unique_ptr<Creature> enemy(new Creature(spawn.type, mTextures, mFonts));
		enemy->setPosition(spawn.x, spawn.y);

		mSceneLayers[Air]->attachChild(std::move(enemy));

		mEnemySpawnPoints.pop_back();
	}
}

void World::destroyEntitiesOutsideView()
{
	Command command;
	command.category = Category::Projectile | Category::EnemyCreature;
	command.action = derivedAction<Entity>([this](Entity& e, sf::Time)
	{
		if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
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
			enemy->checkAggro(playerPosition);
			if (enemy->isAggroed() && enemy->isGuided())
				enemy->guideTowards(playerPosition);
			
			float enemyDistance = distance(*mPlayerCreature, *enemy);
			if (enemyDistance < 10.f)
				enemy->attack();
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

	return bounds;
}