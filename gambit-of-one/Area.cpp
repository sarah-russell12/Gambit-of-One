/*
Area.cpp

Date Created: July 4, 2016

Defines all the methods declared in Area.h
*/

#include "Area.h"
#include "DataTables.hpp"
#include "Projectile.hpp"
#include "Pickup.hpp"
#include "Foreach.hpp"
#include "EntityFactory.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>
#include <limits>

namespace
{
	const std::map<sf::Vector2f, AreaData> Map = initializeAreaData();
	EntityFactory Factory{};
}

Area::Area(sf::RenderWindow& window, const TextureHolder& textures, CommandQueue* queue, sf::Vector2f coords, PlayerCreature* player)
	: mCoordinates(coords)
	, mWindow(window)
	, mView(window.getDefaultView())
	, mAreaBounds(0.f, 0.f, mView.getSize().x, mView.getSize().y)
	, mSceneGraph()
	, mSceneLayers()
	, mCommandQueue(queue)
	, mPlayer(player)
	, mData(Map.at(coords))
	, mActiveEnemies()
{
	buildScene(textures);
}

void Area::update(sf::Time dt)
{
	sf::Vector2f velocity = mPlayer->getVelocity();
	
	// The view does not move

	mPlayer->setVelocity(0.f, 0.f);

	guideEntities();

	while (!mCommandQueue->isEmpty()) mSceneGraph.onCommand(mCommandQueue->pop(), dt);

	adaptPlayerVelocity();

	handleCollisions();
	mSceneGraph.removeWrecks();
	mSceneGraph.update(dt, *mCommandQueue);
	
	adaptPlayerPosition();
}

void Area::draw()
{
	mWindow.setView(mView);
	mWindow.draw(mSceneGraph);
}

bool Area::hasAlivePlayer() const
{
	return !mPlayer->isMarkedForRemoval();
}

bool Area::hasPlayerLeftArea() const
{
	return !mAreaBounds.contains(mPlayer->getPosition());
}

void Area::buildScene(const TextureHolder & textures)
{
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		Category::Type category = (i == Ground)
			? Category::SceneGroundLayer : Category::None;

		SceneNode::Ptr layer(new SceneNode(category));
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	auto texture = textures.get(mData.bgTexture);
	sf::IntRect textureRect(mAreaBounds);
	texture.setRepeated(true);

	std::shared_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mAreaBounds.left, mAreaBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	std::shared_ptr<PlayerCreature> player(mPlayer);
	mSceneLayers[Ground]->attachChild(std::move(player));

	std::vector<Creature*> enemies = Factory.getCreatures(mData.enemySpawns);
	FOREACH(auto enemy, enemies)
	{
		std::shared_ptr<Creature> nextEnemy(enemy);

		mSceneLayers[Ground]->attachChild(std::move(nextEnemy));
	}

	std::vector<Scenery*> props = Factory.getScenery(mData.scenerySpawns);
	FOREACH(auto prop, props)
	{
		std::shared_ptr<Scenery> nextProp(prop);

		mSceneLayers[Ground]->attachChild(std::move(nextProp));
	}
}

void Area::adaptPlayerPosition()
{
	sf::FloatRect viewBounds = getViewBounds();
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayer->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayer->setPosition(position);
}

void Area::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayer->getVelocity();

	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayer->setVelocity(velocity / std::sqrt(2.f));
}

sf::FloatRect Area::getViewBounds() const
{
	return sf::FloatRect(mView.getCenter() - mView.getSize() / 2.f, mView.getSize());
}

sf::FloatRect Area::getBattlefieldBounds() const
{
	sf::FloatRect bounds = getViewBounds();
	bounds.top -= 10.f;
	bounds.height += 10.f;
	bounds.left -= 10.f;
	bounds.width += 10.f;

	return bounds;
}

void Area::guideEntities()
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

		sf::Vector2f playerPosition = mPlayer->getWorldPosition();
		FOREACH(Creature* enemy, mActiveEnemies)
		{
			enemy->guideTowards(playerPosition);
		}
	});

	mCommandQueue->push(enemyCollector);
	mCommandQueue->push(creatureGuider);
	mActiveEnemies.clear();
}

void Area::destroyProjectilesOutsideView()
{
	// We should only need to destroy the projectiles outside the view
	// Maybe one day there can be an AI thing where creatures at low
	// health can run away
	Command command;
	command.category = Category::Projectile; //| Category::EnemyCreature;
	command.action = derivedAction<Entity>([this](Entity& e, sf::Time)
	{
		if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
			e.destroy();
	});

	mCommandQueue->push(command);
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

void Area::handleCollisions()
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
			// Creatures will be stopped from going in the direction that they are
			// colliding with the Scenery, but will not turn around
			auto& creature = static_cast<Creature&>(*pair.first);
			auto& scenery = static_cast<Scenery&>(*pair.second);

			sf::FloatRect creatureBounds = creature.getBoundingRect();
			sf::FloatRect objectBounds = scenery.getBoundingRect();
			sf::Vector2f pos;
			// If a creature is moving up, it will collide halfway with any scenery.
			// Kind of looks like it is walking up to the scenery item.
			// Movement should be unrestricted until
			if (creatureBounds.top < (objectBounds.top + objectBounds.height)
				&& (creatureBounds.top + creatureBounds.height) >(objectBounds.top + objectBounds.height))
			{
				if (scenery.getBoundingRect().contains(creature.getPosition()))
				{
					creature.block();
					pos.x = creature.getPosition().x;
					pos.y = objectBounds.top + objectBounds.height + 5.f;
					creature.setPosition(pos);
				}
			}
			else
			{
				// Just block it normally
				creature.block();
				switch (creature.getCompass())
				{
				case Creature::North:
					pos.x = creature.getPosition().x;
					pos.y = objectBounds.top + objectBounds.height + 5.f;
					creature.setPosition(pos);
					break;
				case Creature::South:
					pos.x = creature.getPosition().x;
					pos.y = objectBounds.top - ((creatureBounds.top + creatureBounds.height) / 2.f) - 5.f;
					creature.setPosition(pos);
					break;
				case Creature::East:
					pos.x = objectBounds.left - 5.f;
					pos.y = creature.getPosition().y;
					creature.setPosition(pos);
					break;
				case Creature::West:
					pos.x = objectBounds.left + objectBounds.width + 5.f;
					pos.y = creature.getPosition().y;
					creature.setPosition(pos);
					break;
				}
			}
		}
		else if (matchesCategories(pair, Category::Projectile, Category::Scenery))
		{
			// Destroy the projectile upon hitting the Scenery blocking it

			auto& projectile = static_cast<Projectile&>(*pair.first);

			projectile.destroy();
		}
	}
}