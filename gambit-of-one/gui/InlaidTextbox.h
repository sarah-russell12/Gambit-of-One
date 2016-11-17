/*
InlaidTextbox.h

Date Created: November 14, 2016

This is just a wrapper for an sf::RectangleShape and an sf::Text together in one class.
This will be used to make the CharacterState look fancy.
*/

#pragma once
#ifndef INLAID_TEXTBOX_H
#define INLAID_TEXTBOX_H

#include "Component.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace GUI {

	class InlaidTextbox : public Component
	{
	public:
		typedef std::shared_ptr<InlaidTextbox> Ptr;

	public:
		InlaidTextbox(const FontHolder& fonts);

		virtual bool		isSelectable() const;
		virtual void		handleEvent(const sf::Event&);

		void				setString(const sf::String& string);
		void				setPosition(const sf::Vector2f& pos);

	private:
		virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Text			mText;
		sf::RectangleShape	mBox;
	};
}

#endif //INLAID_TEXTBOX_H

