/*
SettingsState.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

In the chapter where we handled player input, we had given the Player class the
ability to change the keys which correspond to its actions, called 'key
binding'.  What we did not do is implement an interface that allows us to
actually use this feature. This is what the Settings State is for.  A Settings
State can also be used to adjust the in game volume of the audio of a game and
can change the graphics quality(if it is a very high-end game that is CPU
intensive, rendering complex textures can be burdensome, so lower graphics
quality allows the game run better on slower, older computers)
*/

#ifndef SETTINGSSTATE_HPP
#define SETTINGSSTATE_HPP

#include "State.hpp"
#include "Player.hpp"
#include "Container.hpp"
#include "Button.hpp"
#include "Label.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>


class SettingsState : public State
{
public:
	SettingsState(StateStack& stack, Context context);

	virtual void					draw();
	virtual bool					update(sf::Time dt);
	virtual bool					handleEvent(const sf::Event& event);


private:
	void							updateLabels();
	void							addButtonLabel(Player::Action action, float y, const std::string& text, Context context);


private:
	sf::Sprite											mBackgroundSprite;
	GUI::Container										mGUIContainer;
	std::array<GUI::Button::Ptr, Player::ActionCount>	mBindingButtons;
	std::array<GUI::Label::Ptr, Player::ActionCount> 	mBindingLabels;
};

#endif // SETTINGSSTATE_HPP