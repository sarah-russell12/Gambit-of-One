/*
CharacterState.h

Date Created: October 27, 2016

The Character State is a visualization of the protagonist's stats.  In this state,
the player can also increase their stats upon leveling.
*/

#pragma once
#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H

#include "State.hpp"
#include "Container.hpp"
#include "InlaidTextbox.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

class CharacterState : public State {
public:
	CharacterState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
	void				buildScreen();
	void				buildStats();

private:
	sf::Text									mInstructionText;
	sf::Text									mHeader;
	GUI::Container								mContainer;
	std::vector<sf::Text>						mStatNames;
	std::vector<GUI::InlaidTextbox::Ptr>		mStatValues;

};

#endif // CHARACTER_STATE_H
