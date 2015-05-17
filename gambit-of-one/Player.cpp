#include "Player.h"

Player::Player()
{
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;

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
		pair.second.category = Category::Player;
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
		output.category = Category::Player;
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