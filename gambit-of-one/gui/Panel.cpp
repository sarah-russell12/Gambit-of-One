/*
Panel.cpp

Date Created: November 10 2016

Defines all the methods declared in Panel.h
*/

#include "Panel.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI 
{

	Panel::Panel(sf::Vector2f size, bool isHorizontal)
		: mBox()
		, mSize()
	{
		mBox.setFillColor(sf::Color(175, 100, 255, 255));
		mBox.setOutlineColor(sf::Color(255, 215, 50, 255));
		mBox.setOutlineThickness(10);
		if (isHorizontal) 
		{
			mBox.setSize(sf::Vector2f(size.x, (size.y / 2.f)));
			mSize = mBox.getSize();
			mBox.setPosition(sf::Vector2f(0, (size.y / 2.f)));
		}
		else
		{
			mBox.setSize(sf::Vector2f((size.x / 2.f), size.y));
			mSize = mBox.getSize();
			mBox.setPosition(sf::Vector2f(0, 0));
		}
	}

	sf::FloatRect Panel::getMeasurements() const
	{
		sf::Vector2f pos = mBox.getPosition();
		return sf::FloatRect(pos.x, pos.y, mSize.x, mSize.y);
	}

	bool Panel::isSelectable() const
	{
		return false;
	}

	void Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mBox, states);
	}

	void Panel::handleEvent(const sf::Event&) {}
}