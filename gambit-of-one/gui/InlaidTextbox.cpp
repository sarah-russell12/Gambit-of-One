/*
InlaidTextbox.cpp

Date Created: November 14, 2016

Defines all the methods declared in InlaidTextbox.h
*/

#include "InlaidTextbox.h"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
	InlaidTextbox::InlaidTextbox(const FontHolder& fonts)
		: mText(), mBox()
	{
		mBox.setSize(sf::Vector2f(60.f, 30.f));
		mBox.setFillColor(sf::Color(0, 0, 0, 150));
		mBox.setOutlineColor(sf::Color(255, 215, 50, 255));
		mBox.setOutlineThickness(5.f);
		//centerOrigin(mBox);

		mText.setFont(fonts.get(Fonts::Display));
		mText.setCharacterSize(16);
		mText.setString("0");
		centerOrigin(mText);
	}

	bool InlaidTextbox::isSelectable() const { return false; }

	void InlaidTextbox::handleEvent(const sf::Event&) {}

	void InlaidTextbox::setString(const sf::String& string)
	{
		// In case the box and text need to have their positions reset
		sf::Vector2f currentPos = mBox.getPosition();
		mText.setString(string);
		
		// In case the text exceeds the size of the box
		float width = std::max(mBox.getGlobalBounds().width, mText.getGlobalBounds().width);
		float height = std::max(mBox.getGlobalBounds().height, mText.getGlobalBounds().height);
		mBox.setSize(sf::Vector2f(width, height));

		// Resetting the positions of the InlaidBox
		centerOrigin(mText);
		//centerOrigin(mBox);
		setPosition(currentPos);
	}

	void InlaidTextbox::setPosition(const sf::Vector2f& pos)
	{
		// The inlaid box position is set by the top left corner of the box
		// The text keeps alligned to the center of the box.
		mBox.setPosition(pos);
		sf::Vector2f boxSize = mBox.getSize();
		float x = pos.x + (boxSize.x / 2.f);
		float y = pos.y + (boxSize.y / 2.f);
		mText.setPosition(sf::Vector2f(x, y));
	}

	void InlaidTextbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mBox, states);
		target.draw(mText, states);
	}
}