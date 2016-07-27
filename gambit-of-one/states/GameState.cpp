/*
GameState.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/

#include "GameState.hpp"


GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mPlayer(*context.player)
	, mPlayerCreature(Creature::Hero, *context.textures, *context.fonts)
	, mCurrentArea(0, 0)
	, mAreaBounds()
	, mQueue()
	, mRequiredKills(2) 
	, mEntityFactory(*context.textures, *context.fonts)
	// Will find some different win condition when non-combatant creatures are added 
{
	mPlayer.setMissionStatus(Player::MissionRunning);
	initializeWorld(context);
}

void GameState::draw()
{
	mWorld[mCurrentArea.x][mCurrentArea.y]->draw();
}

bool GameState::update(sf::Time dt)
{
	mWorld[mCurrentArea.x][mCurrentArea.y]->update(dt);

	if (!mWorld[mCurrentArea.x][mCurrentArea.y]->hasAlivePlayer())
	{
		mPlayer.setMissionStatus(Player::MissionFailure);
		requestStackPush(States::GameOver);
	}
	else if (mPlayerCreature.getKillCount() == mRequiredKills)
	{
		mPlayer.setMissionStatus(Player::MissionSuccess);
		requestStackPush(States::GameOver);
	}
	else if (mWorld[mCurrentArea.x][mCurrentArea.y]->hasPlayerLeftArea())
	{
		changeArea();
	}

	mPlayer.handleRealtimeInput(mQueue);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// Game input handling
	mPlayer.handleEvent(event, mQueue);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	return true;
}

void GameState::initializeWorld(Context context)
{
	for (int i = 0; i < 2; i++)
	{
		mWorld.push_back(std::vector<Area*>());
		for (int j = 0; j < 2; j++)
		{
			mWorld[i].push_back(new Area(*context.window, *context.textures, &mQueue, i, j, &mPlayerCreature, &mEntityFactory));
		}
	}

	sf::View view =  sf::View{context.window->getDefaultView() };
	mCurrentArea = sf::Vector2i(0, 0);
	mPlayerCreature.setPosition(view.getSize().x / 2.f, view.getSize().y / 2.f);
	mAreaBounds = sf::FloatRect{ 0.f, 0.f, view.getSize().x, view.getSize().y };
}

void GameState::changeArea()
{
	sf::Vector2f pos = mPlayerCreature.getPosition();
	float widthMargin = mPlayerCreature.getBoundingRect().width / 2.f;
	float heightMargin = mPlayerCreature.getBoundingRect().height / 2.f;
	if (pos.x > mAreaBounds.width)
	{
		assert(mCurrentArea.x < mWorld.size() - 1);
		mCurrentArea.x += 1;
		mPlayerCreature.setPosition(widthMargin, pos.y);
		return;
	}
	if (pos.x < mAreaBounds.left)
	{
		assert(mCurrentArea.x > 0);
		mCurrentArea.x -= 1;
		mPlayerCreature.setPosition(mAreaBounds.width - widthMargin, pos.y);
		return;
	}
	if (pos.y > mAreaBounds.height)
	{
		assert(mCurrentArea.y < mWorld[mCurrentArea.x].size() - 1);
		mCurrentArea.y += 1;
		mPlayerCreature.setPosition(pos.x, heightMargin);
	}
	if (pos.y < mAreaBounds.top)
	{
		assert(mCurrentArea.y > 0);
		mCurrentArea.y -= 1;
		mPlayerCreature.setPosition(pos.x, mAreaBounds.height - heightMargin);
	}
}