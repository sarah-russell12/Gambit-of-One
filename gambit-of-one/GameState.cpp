#include "Headers/GameState.h"

GameState::GameState(StateStack& stack, Context context) :
State(stack, context),
mWorld(*context.window, *context.fonts),
mPlayer(*context.player)
{
	
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	if (!mWorld.hasAlivePlayer())
	{
		mPlayer.setStatus(Player::Failure);
		requestStackPush(States::GameOver);
	}
	else if (mWorld.allEnemiesDefeated())
	{
		mPlayer.setStatus(Player::Success);
		requestStackPush(States::GameOver);
	}

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	mPlayer.handleRealtimeInput(commands);

	return true;
}

