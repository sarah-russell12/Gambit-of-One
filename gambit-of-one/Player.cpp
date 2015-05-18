#include "Player.h"

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
{
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
	mKeyBinding[sf::Keyboard::Space] = Attack;
	mKeyBinding[sf::Keyboard::F] = FireArrow;

	initializeActions();

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
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end()
			&& !isRealtimeAction(found->second))
		{
			commands.push(mActionBinding[found->second]);
		}
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
	mActionBinding[MoveLeft].action = derivedAction<Creature>(CreatureMover(-1, 0));
	mActionBinding[MoveRight].action = derivedAction<Creature>(CreatureMover(+1, 0));
	mActionBinding[MoveUp].action = derivedAction<Creature>(CreatureMover(0, -1));
	mActionBinding[MoveDown].action = derivedAction<Creature>(CreatureMover(0, +1));
	mActionBinding[Attack].action = derivedAction<Creature>(std::bind(&Creature::attack, _1));
	mActionBinding[FireArrow].action = derivedAction<Creature>(std::bind(&Creature::fireArrow, _1));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveUp:
	case MoveDown:
	case Attack:
		return true;
	default:
		return false;
	}
}

void Player::setStatus(Status status)
{
	mStatus = status;
}

Player::Status Player::getStatus() const
{
	return mStatus;
}

