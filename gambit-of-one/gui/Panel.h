/*
Panel.h

Date Created: November 10, 2016

A panel is a GUI Element that acts as a backdrop for displaying information.
It takes up half of the game screen.
*/

#pragma once
#ifndef PANEL_H
#define PANEL_H

#include "Component.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace GUI 
{

	class Panel : public Component {
	public:
		typedef std::shared_ptr<Panel>		Ptr;

	public:
		Panel(sf::Vector2f size, bool isHorizontal = false);

		sf::FloatRect		getMeasurements() const;

		virtual bool		isSelectable() const;
		virtual void		handleEvent(const sf::Event&);

	private:
		virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Vector2f		mSize;
		sf::RectangleShape	mBox;
	};

}
#endif // PANEL_H