#ifndef WORLD_H
#define WORLD_H
#include "SFML_facilities.h"
#include "ResourceHolder.hpp"
#include "SceneNode.h"
#include <array>
#include "SpriteNode.h"
#include <SFML/System/NonCopyable.hpp>
#include "CommandQueue.h"

class World : public sf::NonCopyable
{
public:
	World();
	explicit			World(sf::RenderWindow& window);
	void				update(sf::Time dt);
	void				draw();
	CommandQueue		getCommandQueue();

private:
	void				loadTextures();
	void				buildScene();

private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};

private:
	sf::RenderWindow&					mWindow;
	sf::View							mWorldView;
	TextureHolder						mTextures;
	SceneNode							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;

	sf::FloatRect						mWorldBounds;
	sf::Vector2f						mSpawnPosition;
	float								mScrollSpeed;
	Aircraft*							mPlayerAircraft;
	CommandQueue						mCommandQueue;
};

#endif //WORLD_H