/*
World.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

World is the object that contains the SceneNodes of the world and helps set up
the view. It also handles collisions in the scene graph.
*/

#ifndef WORLD_HPP
#define WORLD_HPP

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Creature.hpp"
#include "PlayerCreature.h"
#include "CommandQueue.hpp"
#include "Command.hpp"
#include "Scenery.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>



#include <array>
#include <queue>

namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
public:
	explicit							World(sf::RenderWindow& window, FontHolder& fonts);
	void								update(sf::Time dt);
	void								draw();

	CommandQueue&						getCommandQueue();

	bool 								hasAlivePlayer() const;
	bool 								hasPlayerReachedEnd() const;


private:
	void								loadTextures();
	void								adaptPlayerPosition();
	void								adaptPlayerVelocity();
	void								handleCollisions();

	void								buildScene();
	void								addEnemies();
	void								addScenery();
	void								addEnemy(Creature::Type type, float relX, float relY);
	void								addSceneryItem(Scenery::Type type, float relX, float relY);
	void								spawnEnemies();
	void								spawnScenery();
	void								destroyEntitiesOutsideView();
	void								guideMissiles();
	void								guideCreatures();
	sf::FloatRect						getViewBounds() const;
	sf::FloatRect						getBattlefieldBounds() const;

	void								sortSpawnPoints();


private:
	enum Layer
	{
		Background,
		Objects,
		Ground,
		LayerCount
	};

	struct SpawnPoint
	{
		SpawnPoint(Creature::Type type, float x, float y)
			: type(type), x(x), y(y) {}

		Creature::Type type;
		float x;
		float y;
	};

	struct ScenerySpawn
	{
		ScenerySpawn(Scenery::Type type, float x, float y)
			: type(type), x(x), y(y) {}

		Scenery::Type type;
		float x;
		float y;
	};


private:
	sf::RenderWindow&					mWindow;
	sf::View							mWorldView;
	TextureHolder						mTextures;
	FontHolder&							mFonts;

	SceneNode							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	CommandQueue						mCommandQueue;

	sf::FloatRect						mWorldBounds;
	sf::Vector2f						mSpawnPosition;
	float								mScrollSpeed;
	PlayerCreature*						mPlayerCreature;

	std::vector<SpawnPoint>				mEnemySpawnPoints;
	std::vector<ScenerySpawn>			mScenerySpawnPoints;
	std::vector<Creature*>				mActiveEnemies;
	std::vector<Scenery*>				mActiveScenery;
};

#endif // WORLD_HPP	