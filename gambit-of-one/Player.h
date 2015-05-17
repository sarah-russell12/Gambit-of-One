#ifndef PLAYER_H
#define PLAYER_H
#include "SFML_facilities.h"
#include "CommandQueue.h"
#include "Command.inl"
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
		Arrow,
		ActionCount,
	};

public:
						Player();
	void				handleEvent(const sf::Event& mEvent, CommandQueue& commands);
	void				handleRealtimeInput(CommandQueue& commands);
	void				assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key	getAssignedKey(Action action) const;

private:
	static bool			isRealtimeAction(Action action);

private:
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command>			mActionBinding;
	float								playerSpeed;
};

#endif //PLAYER_H