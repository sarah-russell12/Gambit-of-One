/*
Label.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/

#include "Label.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

	Label::Label(const std::string& text, const FontHolder& fonts)
		: mText(text, fonts.get(Fonts::Display), 16)
	{
	}

	bool Label::isSelectable() const
	{
		return false;
	}

	void Label::handleEvent(const sf::Event&)
	{
	}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mText, states);
	}

	void Label::setText(const std::string& text)
	{
		mText.setString(text);
	}

}