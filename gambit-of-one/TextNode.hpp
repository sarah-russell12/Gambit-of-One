/*
TextNode.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

The TextNode is a wrapper for sf::Text that fits into the SceneGraph structure.
*/

#ifndef TEXTNODE_HPP
#define TEXTNODE_HPP

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>


class TextNode : public SceneNode
{
public:
	explicit			TextNode(const FontHolder& fonts, const std::string& text);

	void				setString(const std::string& text);


private:
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	sf::Text			mText;
};

#endif // TEXTNODE_HPP