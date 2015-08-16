/*
PauseState.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

The PauseState works as a manual break that the player can call on in order to
step away from the game.  It renders itself keeping in mind that the states
that exist below it on the stack will be rendered before it. From this state,
the user can return to the main menu or return to playing the game.
*/

#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "Container.hpp"
#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mPausedText;
	GUI::Container 		mGUIContainer;
};

#endif // PAUSESTATE_HPP