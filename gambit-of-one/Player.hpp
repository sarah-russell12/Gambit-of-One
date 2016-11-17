/*
Player.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

The Player class is what handles input from the user.  It also keeps track
of the keybindings for commands and whether or not a player has succeeded in
completing the level.
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Command.hpp"
#include "DataTables.hpp"

#include <SFML/Window/Event.hpp>

#include <map>
#include <vector>


class CommandQueue;

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
		Fire,
		ActionCount
	};

	enum MissionStatus
	{
		MissionRunning,
		MissionSuccess,
		MissionFailure
	};


public:
	Player();

	void					handleEvent(const sf::Event& event, CommandQueue& commands);
	void					handleRealtimeInput(CommandQueue& commands);

	void					assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key		getAssignedKey(Action action) const;

	void 					setMissionStatus(MissionStatus status);
	void					checkMissionStatus();
	MissionStatus 			getMissionStatus() const;

	CreatureData			getPlayerStats() const;
	void					setPlayerStats(std::vector<unsigned int> stats);
	void					setPlayerStats(CreatureData data);

private:
	void					initializeActions();
	static bool				isRealtimeAction(Action action);


private:
	std::map<sf::Keyboard::Key, Action>		mKeyBinding;
	std::map<Action, Command>				mActionBinding;
	MissionStatus 							mCurrentMissionStatus;

	CreatureData							mPlayerStats;
};

#endif // PLAYER_HPP