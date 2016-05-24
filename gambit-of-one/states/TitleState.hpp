/*
TitleState.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

The TitleState in terms of program logic is the first state that is ever run in
the program. In terms of player experience, the TitleState is the first screen
of a game usually displaying the Title of the game in nice, fancy graphics.
*/

#ifndef TITLESTATE_HPP
#define TITLESTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mText;

	bool				mShowText;
	sf::Time			mTextEffectTime;
};

#endif // TITLESTATE_HPP