/*
StateStack.hpp

Date Last Updated: June 21, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
- Moved to "Headers" folder
- Opted to not use most of "facilities" header files anymore
*/

#ifndef STATE_STACK_HPP
#define STATE_STACK_HPP

#include "Enumerations.hpp"
#include "SFML_facilities.h"
#include "State.h"

#include <assert.h>
#include <cassert>
#include <vector>
#include <map>
#include <functional>

class StateStack : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};

public:
	explicit			StateStack(State::Context context);
	template<typename T>
	void				registerState(States::ID stateID);
	void				update(sf::Time dt);
	void				draw();
	void				pushState(States::ID stateID);
	void				popState();
	void				clearStates();
	void				handleEvent(const sf::Event& event);

	bool				isEmpty() const;

private:
	State::Ptr			createState(States::ID stateID);
	void				applyPendingChanges();

private:
	struct PendingChange
	{
		Action			action;
		States::ID		stateID;
	};

private:
	std::vector<State::Ptr>				mStack;
	std::vector<PendingChange>			mPendingList;
	State::Context						mContext;
	std::map < States::ID,
		std::function < State::Ptr() >> mFactories;
};

#include "StateStack.inl"

#endif //STATE_STACK_HPP