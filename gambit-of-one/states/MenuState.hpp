/*
MenuState.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

The menu state is the state beyond the title state.  In this state the user can
start gameplay or exit the program. It also allows the player to enter a
SettingsState that alters the keybindings of the actions in the game.
*/

#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "State.hpp"
#include "..\gui\Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);


private:
	sf::Sprite				mBackgroundSprite;
	GUI::Container			mGUIContainer;
};

#endif // MENUSTATE_HPP