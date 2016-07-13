/*
Area.h

Date Created: July 4, 2016

This class offers independence (hehe) from the hard-coded mess that was World.
It has most of the functions of World; however, this is meant to only take up
one screen at a time, and does not directly know what it will look like when
constructing itself, and the exiting of one area leads to another area, if data
exists for it.
*/

#pragma once
#ifndef AREA_H
#define AREA_H

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "PlayerCreature.h"
#include "CommandQueue.hpp"
#include "Command.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <queue>
#include <vector>

namespace sf
{
	class RenderWindow;
}

class Area : private sf::NonCopyable
{
public:
	// Long, but hopefully worth it
	Area(sf::RenderWindow& window, const TextureHolder& textures, CommandQueue* queue, int x, int y, PlayerCreature* player);

	void			update(sf::Time dt);
	void			draw();

	bool			hasAlivePlayer() const;
	bool			hasPlayerLeftArea() const;

private:
	void			buildScene();

	void			adaptPlayerPosition();
	void			adaptPlayerVelocity();

	sf::FloatRect	getViewBounds() const;
	sf::FloatRect	getBattlefieldBounds() const;

	void			guideEntities();
	void			destroyProjectilesOutsideView();
	void			handleCollisions();

	void			handleSceneryCollision(SceneNode::Pair pair);

private:
	enum Layer
	{
		Background,
		Objects,
		Ground,
		LayerCount
	};

private:
	sf::Vector2i						mCoordinates;
	sf::RenderWindow&					mWindow;
	sf::View							mView;
	sf::FloatRect						mAreaBounds;

	SceneNode							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	CommandQueue*						mCommandQueue;

	PlayerCreature*						mPlayer;
	AreaData							mData;

	std::vector<Creature*>				mActiveEnemies;

	sf::Texture							mBackground;
};

#endif //AREA_H