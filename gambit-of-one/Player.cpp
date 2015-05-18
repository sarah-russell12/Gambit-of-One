#include "Player.h"
#include "Aircraft.h"

Player::Player()
{
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
	mKeyBinding[sf::Keyboard::Space] = Fire;
	mKeyBinding[sf::Keyboard::M] = LaunchMissile;

	mActionBinding[MoveLeft].action =
		[](SceneNode& node, sf::Time dt)
	{
		node.move(-30.f * dt.asSeconds(), 0.f);
	};

	mActionBinding[MoveRight].action =
		[](SceneNode& node, sf::Time dt)
	{
		node.move(30.f * dt.asSeconds(), 0.f);
	};

	mActionBinding[MoveUp].action =
		[](SceneNode& node, sf::Time dt)
	{
		node.move(0.f, -30.f * dt.asSeconds());
	};

	mActionBinding[MoveDown].action =
		[](SceneNode& node, sf::Time dt)
	{
		node.move(0.f, -30.f * dt.asSeconds());
	};

	for (auto& pair : mActionBinding)
	{
		pair.second.category = Category::PlayerAircraft;
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	for (auto pair : mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first)
			&& isRealtimeAction(pair.second))
		{
			commands.push(mActionBinding[pair.second]);
		}
	}
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed
		&& event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [](SceneNode& s, sf::Time)
		{
			std::cout << s.getPosition().x << ","
				<< s.getPosition().y << "\n";
		};
		commands.push(output);
	}
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveDown:
	case MoveLeft:
	case MoveUp:
	case MoveRight:
		return true;
	default:
		return false;
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	for (auto pair : mKeyBinding) 
	{
		if (pair.second == action) 
		{
			auto pos = mKeyBinding.find(pair.first);
			mKeyBinding.erase(pos);
			mKeyBinding[key] = action;
			return;
		}
	}
	mKeyBinding[key] = action;
}

void Player::initializeActions()
{
	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-1, 0));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+1, 0));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0, -1));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0, +1));
	mActionBinding[Fire].action = derivedAction<Aircraft>(std::bind(&Aircraft::fire, _1));
	mActionBinding[LaunchMissile].action = derivedAction<Aircraft>(std::bind(&Aircraft::launchMissile, _1));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
		case MoveLeft:
		case MoveRight:
		case MoveUp:
		case MoveDown:
		case Fire:
			return true;
		default:
			return false;
}