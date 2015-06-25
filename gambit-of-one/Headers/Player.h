/*
Player.h

Date Last Updated: June 21, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use most of "facilities" header files anymore
- June 25, 2015:
	- implemented previously unimplemented method
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "SFML_facilities.h"
#include "Command.hpp"
#include "CommandQueue.h"
#include "Creature.hpp"
#include "UtilityFunctions.hpp"

#include <iostream>
#include <map>

class Player
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Attack,
		FireArrow,
		ActionCount,
	};

	enum Status
	{
		Running,
		Success,
		Failure,
	};

public:
						Player();
	void				handleEvent(const sf::Event& mEvent, CommandQueue& commands);
	void				handleRealtimeInput(CommandQueue& commands);
	void				assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key	getAssignedKey(Action action) const;

	void				setStatus(Status status);
	Status				getStatus() const;

private:
	static bool			isRealtimeAction(Action action);
	void				initializeActions();

private:
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command>			mActionBinding;
	Status								mStatus;
};

#endif //PLAYER_H