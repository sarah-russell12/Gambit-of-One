/*
Portrait.h

Date Created: April 16, 2016

A Portrait is the picture of an important character that renders when speaking
to one in-game.
*/

#pragma once
#ifndef GUI_PORTRAIT_H
#define GUI_PORTRAIT_H

#include "Component.hpp"
#include "Creature.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace GUI
{
	class Portrait : public Component
	{
	public:
		typedef std::shared_ptr<Portrait> Ptr;

	public:
		Portrait(const TextureHolder& textures, Creature* creature);

		virtual bool		isSelectable() const;

		virtual void		handleEvent(const sf::Event& evnt);

	private:
		virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Sprite			mSprite;
		Creature*			mCharacter;
	};
}

#endif //GUI_PORTRAIT_H