/*
MenuState.h

Date Last Updated: June 20, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use "facilities" header files anymore
*/

#ifndef MENU_STATE_H
#define MENU_STATE_H


#include "Button.h"
#include "Container.h"
#include "State.h"
#include "StateStack.hpp"

#include <vector>

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context& context);
	
	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);

private:
	GUI::Container					mGUIContainer;
	sf::Sprite						mBackgroundSprite;
};


#endif //MENU_STATE_H