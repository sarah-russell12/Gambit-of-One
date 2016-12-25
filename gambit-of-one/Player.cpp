/*
Player.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/

#include "Player.hpp"
#include "CommandQueue.hpp"
#include "Creature.hpp"
#include "Foreach.hpp"
#include "DataTables.hpp"

#include <map>
#include <string>
#include <algorithm>


using namespace std::placeholders;


struct CreatureMover
{
	CreatureMover(float vx, float vy)
		: velocity(vx, vy)
	{
	}

	void operator() (Creature& creature, sf::Time) const
	{
		creature.accelerate(velocity * creature.getMaxSpeed());
	}

	sf::Vector2f velocity;
};

Player::Player()
	: mCurrentMissionStatus(MissionRunning), mCurrentLevelStatus(None), mPointPool(0), mNextLevel(50)
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::A] = MoveLeft;
	mKeyBinding[sf::Keyboard::D] = MoveRight;
	mKeyBinding[sf::Keyboard::W] = MoveUp;
	mKeyBinding[sf::Keyboard::S] = MoveDown;
	mKeyBinding[sf::Keyboard::Space] = Attack;
	mKeyBinding[sf::Keyboard::F] = Fire;

	// Set initial action bindings
	initializeActions();

	// Assign all categories to player's aircraft
	FOREACH(auto& pair, mActionBinding)
		pair.second.category = Category::PlayerCreature;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	FOREACH(auto pair, mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();)
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	FOREACH(auto pair, mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::setMissionStatus(MissionStatus status)
{
	mCurrentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
	return mCurrentMissionStatus;
}

CreatureData Player::getPlayerStats() const
{
	return mPlayerStats;
}

void Player::setPlayerStats(int stats[], unsigned int leftover)
{
	mPlayerStats.strength = stats[0];
	mPlayerStats.dexterity = stats[1];
	mPlayerStats.intelligence = stats[2];
	mPlayerStats.constitution = stats[3];
	mPlayerStats.charisma = stats[4];

	if (leftover == 0)
	{
		mCurrentLevelStatus = None;
	}
	mPointPool = leftover;
}

void Player::setPlayerStats(CreatureData data)
{
	mPlayerStats = data;
}

Player::LevelStatus Player::getLevelStatus() const
{
	return mCurrentLevelStatus;
}

unsigned int Player::getPoints() const
{
	return mPointPool;
}

unsigned int Player::getLevelThreshold() const
{
	return mNextLevel;
}

void Player::initializeActions()
{
	mActionBinding[MoveLeft].action = derivedAction<Creature>(CreatureMover(-1, 0));
	mActionBinding[MoveRight].action = derivedAction<Creature>(CreatureMover(+1, 0));
	mActionBinding[MoveUp].action = derivedAction<Creature>(CreatureMover(0, -1));
	mActionBinding[MoveDown].action = derivedAction<Creature>(CreatureMover(0, +1));
	mActionBinding[Attack].action = derivedAction<Creature>([](Creature& a, sf::Time) { a.setAction(Attack); a.attack(); });
	mActionBinding[Fire].action = derivedAction<Creature>([](Creature& a, sf::Time) { a.setAction(Fire);  a.attack(); });
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveDown:
	case MoveUp:
		return true;

	default:
		return false;
	}
}

void Player::onLevelUp()
{
	if (mCurrentLevelStatus != UnallocatedPoints)
	{
		mPlayerStats.level += 1;
		mCurrentLevelStatus = UnallocatedPoints;
		mPointPool += 5;
		mNextLevel += 50;
	}
}