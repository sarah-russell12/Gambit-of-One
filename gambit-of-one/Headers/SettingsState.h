/*
	SettingsState.h

	Date Last Updated: April 16, 2015

	This header file was made during the Spring 2015 SFML Game Development
	Tutorial at New College of Florida.  This code follows the code from the
	textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
	Hansson, and Jan Haller.
*/

#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "States_Facilities.h"
#include "Gui_Facilities.h"
#include <functional>
#include <memory>
#include <string>

class SettingsState : public State
{
public:
	SettingsState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
	void				updateLabels();
	void				addButtonLabel(Player::Action action, float y, const std::string& text, Context context);

private:
	sf::Sprite											mBackgroundSprite;
	GUI::Container										mGUIContainer;
	std::array<GUI::Button::Ptr, Player::ActionCount>	mBindingButtons;
	std::array<GUI::Label::Ptr, Player::ActionCount> 	mBindingLabels;
};


#endif //SETTINGS_STATE_H