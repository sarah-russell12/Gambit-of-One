/*
Portrait.cpp

Date Created: April 16, 2016

Defines all the methods declared in Portrait.h
*/

#include "Portrait.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
	Portrait::Portrait(const TextureHolder& textures, Creature* creature)
		: mSprite()
		, mCharacter(creature)
	{
		// TODO:
		// Determine how Special Characters portraits are stored while in game
	}

	bool Portrait::isSelectable() const
	{
		return false;
	}

	void Portrait::handleEvent(const sf::Event& evnt) {}

	void Portrait::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mSprite, states);
	}
}