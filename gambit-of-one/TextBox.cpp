/*
TextBox.cpp

Date Created: April 16, 2016

Defines all the methods declared in TextBox.h
*/

#include "TextBox.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace GUI
{
	TextBox::TextBox(const FontHolder& fonts, sf::RenderWindow& window)
		: mText("", fonts.get(Fonts::Main), 18)
		, mBox()
		, mLineFinished(true)
	{
		// Size and position of the textbox is meant to be relative to the
		// size of 
		mBox.setFillColor(sf::Color(200, 120, 255));
		mBox.setOutlineColor(sf::Color(255, 230, 120));
		mBox.setOutlineThickness(5.f);

		sf::Vector2u size = window.getSize();
		sf::Vector2f boxSize((4.f * size.x) / 5.f, (1.f / 5.f) * size.y);
		mBox.setSize(boxSize);

		float posX = size.x / 6.f;
		float posY = size.y / 10.f;
		mBox.setPosition(posX, posY);

		mText.setPosition(posX + 10.f, posY + 10.f);
	}

	bool TextBox::isSelectable() const
	{
		return false;
	}

	void TextBox::handleEvent(const sf::Event& evnt)
	{

	}

	void TextBox::nextLine()
	{
		if (!mLineFinished)
		{
			mIndex++;
			if (mIndex < mLineQueue.size())
			{
				mText.setString(mLineQueue[mIndex]);
				
				// TODO: Check how to limit the text to the bounds of 10px within mBox
			}
			else
			{
				mLineFinished = true;
			}
		}
	}

	void TextBox::setLines(std::vector<std::string> lines)
	{
		if (mLineFinished)
		{
			mLineQueue = lines;
		}
	}

	void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mBox, states);
		target.draw(mText, states);
	}
}