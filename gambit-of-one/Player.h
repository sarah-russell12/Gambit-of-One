#ifndef PLAYER_H
#define PLAYER_H
#include "SFML_facilities.h"
#include "CommandQueue.h"
#include "Command.inl"
#include "Creature.h"
#include <iostream>

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