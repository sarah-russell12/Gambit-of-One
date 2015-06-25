/*
TextNode.h

Date Last Updated: June 21, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use most of "facilities" header files anymore
*/

#ifndef TEXT_NODE_H
#define TEXT_NODE_H

#include "ResourceHolder.hpp"
#include "SceneNode.h"
#include "SFML_facilities.h"
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