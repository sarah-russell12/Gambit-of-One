/*
TextNode.h

Sarah Russell

Date Last Updated: July 25, 2015

The TextNode is a wrapper for sf::Text that fits into the SceneGraph structure
created in Chapter 3.

Updates:
- July 25, 2015: Declared TextNode
*/

#ifndef TEXT_NODE_H
#define TEXT_NODE_H

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>

#include "Identifiers.hpp"
#include "ResourceHolder.hpp"
#include "SceneNode.h"

class TextNode : public SceneNode
{
public:
	explicit		TextNode(const FontHolder& fonts, const std::string& text);
	void			setString(const std::string& text);

private:
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Text		mText;
};

#endif //TEXT_NODE_H