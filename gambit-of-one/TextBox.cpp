/*
TextBox.cpp

Date Created: April 16, 2016

Defines all the methods declared in TextBox.h
*/

#include "TextBox.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>

namespace GUI
{
	TextBox::TextBox(const FontHolder& fonts)
		: mText("", fonts.get(Fonts::Main), 18)
		, mBox()
	{
		mBox.setFillColor(sf::Color(200, 120, 255));
		mBox.setOutlineColor(sf::Color(255, 230, 120));
		mBox.setOutlineThickness(5.f);
	}
}