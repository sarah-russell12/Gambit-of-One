/*
SpriteNode.h

Sarah Russell

Date Last Updated: July 20, 2015

SpriteNode is a SceneNode subclass that simply contains an sf::Sprite object
that can be plugged into the SceneNode structure.

Updates:
- July 20, 2015: Declared SpriteNode
*/

#ifndef SPRITE_NODE_H
#define SPRITE_NODE_H

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "SceneNode.h"

class SpriteNode : public SceneNode
{
public:
	explicit			SpriteNode(const sf::Texture& texture);
						SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

private:
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite			mSprite;
};


#endif //SPRITE_NODE_H