#ifndef WORLD_H
#define WORLD_H

#include "SFML_facilities.h"
#include "Entities_Facilities.h"
#include "ResourceHolder.hpp"
#include "CommandQueue.h"
#include "Command.hpp"

#include <SFML/System/NonCopyable.hpp>

#include <array>
#include <queue>

class World : public sf::NonCopyable
{
public:
	World();
	explicit			World(sf::RenderWindow& window, FontHolder& fonts);
	void				update(sf::Time dt);
	void				draw();
	CommandQueue		getCommandQueue();


private:
	void				loadTextures();
	void				buildScene();
	
	void				spawnEnemies();
	void				addEnemy(Creature::Type type, float relX, float relY);
	void				addEnemies();


	sf::FloatRect		getBattlefieldBounds() const;
	sf::FloatRect		getViewBounds() const;

	void				guideMissiles();
	
	void				adaptPlayerPosition();
	void				adaptPlayerVelocity();
	void				handleCollisions();

	void				destroyEntitiesOutsideView();
	void				guideEnemies();

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