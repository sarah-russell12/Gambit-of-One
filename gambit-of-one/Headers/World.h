/*
World.h

Date Last Updated: June 22, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use most of "facilities" header files anymore
- June 24, 2015:
	- Implemented adaptPlayerVelocity() and adaptPlayerPosition()
	  in World.cpp
	- Rearranged methods in World.cpp
*/

#ifndef WORLD_H
#define WORLD_H

#include "Command.hpp"
#include "CommandQueue.h"
#include "Creature.hpp"
#include "Enumerations.hpp"
#include "SceneNode.h"
#include "SFML_facilities.h"
#include "SpriteNode.h"
#include "ResourceHolder.hpp"

#include <array>
#include <queue>

class World : public sf::NonCopyable
{
public:
	World();
	explicit			World(sf::RenderWindow& window, FontHolder& fonts);
	void				update(sf::Time dt);
	void				draw();
	CommandQueue&		getCommandQueue();

	bool				hasAlivePlayer() const;
	bool				allEnemiesDefeated() const;


private:
	void				loadTextures();
	void				buildScene();
	
	void				spawnEnemies();
	void				addEnemy(Creature::Type type, float relX, float relY);
	void				addEnemies();


	sf::FloatRect		getBattlefieldBounds() const;
	sf::FloatRect		getViewBounds() const;

	void				guideEnemies();
	
	void				adaptPlayerPosition();
	void				adaptPlayerVelocity();
	void				handleCollisions();

	void				destroyEntitiesOutsideView();

private:
	enum Layer
	{
		Background,
		Ground,
		LayerCount
	};

	struct SpawnPoint
	{
		SpawnPoint(Creature::Type type, float x, float y)
			: type(type), x(x), y(y) {}
		Creature::Type	type;
		float x;
		float y;
	};

private:
	sf::RenderWindow&					mWindow;
	sf::View							mWorldView;
	TextureHolder						mTextures;
	FontHolder							mFonts;
	SceneNode							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	
	sf::Vector2f						mSpawnPosition;
	Creature*							mPlayerAvatar;
	float								mScrollSpeed;
	CommandQueue						mCommandQueue;

	sf::FloatRect						mWorldBounds;

	std::vector<SpawnPoint>				mEnemySpawnPoints;
	std::vector<Creature*>				mActiveEnemies;

};

#endif //WORLD_H