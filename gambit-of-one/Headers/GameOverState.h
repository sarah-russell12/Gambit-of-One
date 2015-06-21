/*
GameOverState.h

Date Last Updated: June 20, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

The Game Over State uses the same structure as the Menu State, rather
than how the book's code structures the Game Over State

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use "facilities" header files anymore
*/

#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "Button.h"
#include "Container.h"
#include "SFML_facilities.h"
#include "State.h"
#include "StateStack.hpp"
#include "UtilityFunctions.hpp"

class GameOverState : public State
{
public:
						GameOverState(StateStack& stack, Context context);
	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
	sf::Text				mGameOverText;
	sf::Time				mElapsedTime;
	GUI::Container			mGUIContainer;
	sf::Sprite				mBackgroundSprite;
};

#endif //GAME_OVER_STATE_H