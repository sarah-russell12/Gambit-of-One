/*
TextBox.h

Date Created: April 16, 2016

TextBox is a box that displays a line of text.  It also holds other lines of
text in a queue to display later.
*/
#pragma once
#ifndef GUI_TEXTBOX_H
#define GUI_TEXTBOX_H

#include "Component.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>


namespace sf
{
	class RenderWindow;
}

namespace GUI
{

	class TextBox : public Component
	{
	public:
		typedef std::shared_ptr<TextBox> Ptr;

	public:
		TextBox(const FontHolder& fonts, sf::RenderWindow& window);

		virtual bool	isSelectable() const;
		
		virtual void	handleEvent(const sf::Event& evnt);

		void			nextLine();
		void			setLines(std::vector<std::string> lines);

	private:
		virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		bool						mLineFinished;
		int							mIndex;
		sf::Text					mText;

		std::vector<std::string>	mLineQueue;

		sf::RectangleShape			mBox;
	};
}

#endif //GUI_TEXTBOX_H
