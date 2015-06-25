/*
PauseState.h

Date Last Updated: June 20, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use most of "facilities" header files anymore
*/

#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "Button.h"
#include "Container.h"
#include "SFML_facilities.h"
#include "State.h"
#include "UtilityFunctions.hpp"

#include <assert.h>


class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context& context);

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);

private:
	sf::Text				mPausedText;
	GUI::Container			mGUIContainer;
};


#endif //PAUSE_STATE_H