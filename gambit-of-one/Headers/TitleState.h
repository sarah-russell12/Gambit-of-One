/*
TitleState.h

Date Last Updated: June 24, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use most of "facilities" header files anymore
- June 24, 2015:
	- Actually implemented draw() ((I'm surprised I haven't done that before))
	  in TitleState.cpp
*/

#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "SFML_facilities.h"
#include "State.h"

class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void				draw();
	virtual bool				update(sf::Time dt);
	virtual bool				handleEvent(const sf::Event& event);

private:
	sf::Sprite					mBackgroundSprite;
	sf::Text					mText;

	bool						mShowText;
	sf::Time					mTextEffectTime;
};


#endif //TITLE_STATE_H