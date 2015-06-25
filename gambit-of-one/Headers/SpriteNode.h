/*
SceneNode.h

Date Last Updated: June 24, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use most of "facilities" header files anymore
- June 24, 2015:
	- Added SpriteNode.cpp. ((Previously, I had thought SpriteNode had not been
	  used anywhere, so I didn't think to add the .cpp file))
*/

#ifndef SPRITE_NODE_H
#define SPRITE_NODE_H

#include "SceneNode.h"
#include "SFML_facilities.h"

class SceneNode;

class SpriteNode : public SceneNode
{
public:
	explicit		SpriteNode(const sf::Texture& texture);
					SpriteNode(const sf::Texture& texture,
								const sf::IntRect& rect);

private:
	virtual void	drawCurrent(sf::RenderTarget& target,
								sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
};

#endif //SPRITE_NODE_H