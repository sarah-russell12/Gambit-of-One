/*
State.h

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
	- Implemented constructors for State and Context
*/

#ifndef STATE_H
#define STATE_H

#include "Enumerations.hpp"
#include "Player.h"
#include "ResourceHolder.hpp"
#include "SFML_facilities.h"

#include <memory>

class StateStack;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures,
			FontHolder& fonts, Player& player);
		sf::RenderWindow*	window;
		TextureHolder*		textures;
		FontHolder*			fonts;
		Player*				player;
	};

public:
						State(StateStack& stack, Context context);
	virtual				~State();
	virtual void		draw() = 0;
	virtual bool		update(sf::Time dt) = 0;
	virtual bool		handleEvent(const sf::Event& event) = 0;

protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStackClear();

	Context				getContext() const;

private:
	StateStack*			mStack;
	Context				mContext;

};

#endif //STATE_H