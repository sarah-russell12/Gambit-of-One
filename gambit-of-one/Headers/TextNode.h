#ifndef TEXT_NODE_H
#define TEXT_NODE_H

#include "SFML_facilities.h"
#include "SceneNode.h"
#include "ResourceHolder.hpp"
#include "UtilityFunctions.hpp"

#include <string>

class TextNode : public SceneNode
{
public:
	explicit		TextNode(const FontHolder& fonts, 
		const std::string& text);

	void			setString(const std::string& text);

private:
	virtual void	drawCurrent(sf::RenderTarget& target, 
		sf::RenderStates states);

private:
	sf::Text		mText;
};

#endif //TEXT_NODE_H