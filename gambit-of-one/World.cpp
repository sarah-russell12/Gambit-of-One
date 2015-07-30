#include "Headers/World.h"

// public

World::World(sf::RenderWindow& window, FontHolder& fonts)
	: mWindow(window)
	, mSceneGraph()
	, mFonts(fonts)
	, mTextures()
	, mSceneLayers()
	, mScrollSpeed(-50.f)
	, mEnemySpawnPoints()
	, mActiveEnemies()
{
	mWorldView = sf::View(window.getDefaultView());
	mWorldBounds = sf::FloatRect(
		0.f,					//left x position
		0.f,					//top y position
		mWorldView.getSize().x,	//width
		2000.f					//height
		);
	mSpawnPosition = sf::Vector2f(
		mWorldView.getSize().x / 2.f,
		mWorldBounds.height - mWorldView.getSize().y
		);
	mPlayerAvatar = nullptr;


	loadTextures();
	buildScene();
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	// The screen is static vertically and follows the player
	// as they move horizontally
	mWorldView.move(mPlayerAvatar->getVelocity().x * dt.asSeconds(), 0.f);
	mPlayerAvatar->setVelocity(0.f, 0.f);

	//Foward commands to the scene graph
	while (!mCommandQueue.isEmpty())
	{
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	}

	sf::Vector2f velocity = mPlayerAvatar->getVelocity();
	if (velocity.x != 0.f && velocity.y != 0.f)
	{
		mPlayerAvatar->setVelocity(velocity / std::sqrt(2.f));
	}
	mPlayerAvatar->accelerate(sf::Vector2f(0.f, mScrollSpeed));

	//Regular update step
	mSceneGraph.update(dt, mCommandQueue);

	sf::FloatRect viewBounds(
		mWorldView.getCenter() - mWorldView.getSize() / 2.f,
		mWorldView.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAvatar->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAvatar->setPosition(position);
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
	return !mPlayerAvatar->isMarkedForRemoval();
}

bool World::allEnemiesDefeated() const
{
	return mActiveEnemies.empty();
}


// private

void World::loadTextures()
{
	mTextures = TextureHolder();
	mTextures.load(Textures::HeroFront, "Media/Textures/HeroFront.png");
	mTextures.load(Textures::Rat, "Media/Textures/Rat.png");
	mTextures.load(Textures::DirtRoad, "Media/Textures/DirtRoadHorizontal.png");
	mTextures.load(Textures::Arrow, "Media/Textures/Arrow.png");
	mTextures.load(Textures::HealthPotion, "Media/Textures/Potion.png");
	mTextures.load(Textures::Quiver, "Media/Textures/Quiver.png");
}


void World::buildScene()
{
	//setting up the graph
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	//setting up the tiled background
	sf::Texture& texture = mTextures.get(Textures::DirtRoad);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(
		new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(
		mWorldBounds.left,
		mWorldBounds.top);
	mSceneLayers[Background]->attachChild(
		std::move(backgroundSprite));

	std::unique_ptr<Creature> hero(
		new Creature(Creature::Hero, mTextures, mFonts));
	mPlayerAvatar = hero.get();
	mPlayerAvatar->setPosition(mSpawnPosition);
	mPlayerAvatar->setVelocity(0.f, 0.f);
	mSceneLayers[Ground]->attachChild(std::move(hero));
}

void World::spawnEnemies()
{
	while (!mEnemySpawnPoints.empty() 
		&& mEnemySpawnPoints.back().y > getBattlefieldBounds().top)
	{
		SpawnPoint spawn = mEnemySpawnPoints.back();

		std::unique_ptr<Creature> enemy(
			new Creature(spawn.type, mTextures, mFonts));
		enemy->setPosition(spawn.x, spawn.y);
		enemy->setRotation(180.f);

		mEnemySpawnPoints.pop_back();
	}
}

void World::addEnemy(Creature::Type type, float relX, float relY)
{
	SpawnPoint spawn(type, mSpawnPosition.x + relX,
		mSpawnPosition.y - relY);
	mEnemySpawnPoints.push_back(spawn);
}

void World::addEnemies()
{
	addEnemy(Creature::Rat, 500.f, 0.f);
	addEnemy(Creature::Rat, 1000.f, 0.f);
	addEnemy(Creature::Rat, 1100.f, + 100.f);
	addEnemy(Creature::Rat, 1100.f, - 100.f);
	addEnemy(Creature::Rat, 1400.f, - 70.f);
	addEnemy(Creature::Rat, 1600.f, - 70.f);
	addEnemy(Creature::Rat, 1400.f, 70.f);
	addEnemy(Creature::Rat, 1600.f, 70.f);

	std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(),
		[] (SpawnPoint lhs, SpawnPoint rhs)
	{
		return lhs.x < rhs.x;
	});
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

void World::guideEnemies()
{
	Command enemyCollector;
	enemyCollector.category = Category::Enemy;
	enemyCollector.action = derivedAction<Creature>(
		[this](Creature& enemy, sf::Time)
	{
		if (!enemy.isDestroyed())
			mActiveEnemies.push_back(&enemy);
	});

	Command beastGuider;
	beastGuider.category = Category::Enemy;
	beastGuider.action = derivedAction<Creature>(
		[this] (Creature& beast, sf::Time)
	{
		if (beast.isGuided())
		{
			beast.guideTowards(mPlayerAvatar->getWorldPosition());
		}
	});

	mCommandQueue.push(enemyCollector);
	mCommandQueue.push(beastGuider);

	mActiveEnemies.clear();
}

void World::adaptPlayerPosition()
{
	sf::FloatRect viewBounds = getViewBounds();
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAvatar->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAvatar->setPosition(position);
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayerAvatar->getVelocity();

	if (velocity.x != 0.f && velocity.y != 0.f)
	{
		mPlayerAvatar->setVelocity(velocity / std::sqrt(2.f));
	}
}

bool matchesCategories(SceneNode::Pair& colliders,
	Category::Type type1, Category::Type type2)
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

	for (SceneNode::Pair pair : collisionPairs)
	{
		if (matchesCategories(pair, 
			Category::Player, Category::Enemy))
		{
			//react to player enemy collision
			//If the player is attacking, the enemy takes damage
			//player takes a physical hit if they are not attacking

			auto& player = static_cast<Creature&>(*pair.first);
			auto& enemy = static_cast<Creature&>(*pair.second);

			if (player.isAttacking()) {
				enemy.damage(player.getDamage());
			}
			else
			{ 
				player.damage(enemy.getDamage());
			}
			
		}
		else if (matchesCategories(pair, 
			Category::Player, Category::Pickup))
		{
			//react to player pickup collision
			//player recieves a buff

			auto& player = static_cast<Creature&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);

			pickup.apply(player);
			pickup.destroy();
		}
		else if (matchesCategories(pair,
			Category::Enemy, Category::AlliedProjectile)
			|| matchesCategories(pair,
			Category::Player, Category::EnemyProjectile))
		{
			//react to aircraft projectile collision
			//the creature is hit and damaged and the projectile is destroyed

			auto& aircraft = static_cast<Creature&>(*pair.first);
			auto& projectile = static_cast<Projectile&>(*pair.second);

			aircraft.damage(projectile.getDamage());
			projectile.destroy();
		}
	}
}