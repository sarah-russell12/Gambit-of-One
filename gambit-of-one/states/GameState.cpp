/*
GameState.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/

#include "GameState.hpp"
#include "DataTables.hpp"
#include "Utility.hpp"

#include <random>
#include <cmath>
#include <ctime>

using namespace Tables;

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mPlayer(*context.player)
	, mPlayerCreature(0, *context.textures, *context.fonts)
	, mCurrentArea(0, 0)
	, mAreaBounds()
	, mQueue()
	, mRequiredKills(0) 
	, mEntityFactory(*context.textures, *context.fonts)
	, mStatusText("", context.fonts->get(Fonts::Main), 12)
	, mPreviousLevelStatus(Player::LevelStatus::None)
	, mHealthBar()
	, mExpBar()
	, mExpBarBase()
	, mHealthBarBase()
	, mHealthText("", context.fonts->get(Fonts::Main), 16)
	, mExpText("", context.fonts->get(Fonts::Main), 16)
	// Will find some different win condition when non-combatant creatures are added 
{
	mPlayer.setMissionStatus(Player::MissionRunning);
	mPlayer.setPlayerStats(mPlayerCreature.getData());
	initializeWorld(context);
	mStatusText.setPosition(sf::Vector2f(context.window->getSize().x - 200.f, 5.f));

	// Makes seeing experience easier to see
	sf::Vector2f size{ 200.f , 25.f };
	mHealthBarBase.setFillColor(sf::Color(128, 0, 0, 255));
	mHealthBarBase.setSize(size);
	mHealthBarBase.setPosition(sf::Vector2f(10.f, 10.f));
	mHealthBarBase.setOutlineThickness(2.f);
	mHealthBarBase.setOutlineColor(sf::Color(255, 255, 255, 255));

	mHealthBar.setFillColor(sf::Color(255, 0, 0, 255));
	mHealthBar.setPosition(sf::Vector2f(10.f, 10.f));
	
	mExpBarBase.setFillColor(sf::Color(0, 77, 0, 255));
	mExpBarBase.setSize(size);
	mExpBarBase.setPosition(sf::Vector2f(10.f, 45.f));
	mExpBarBase.setOutlineThickness(2.f);
	mExpBarBase.setOutlineColor(sf::Color(255, 255, 255, 255));

	mExpBar.setFillColor(sf::Color(0, 255, 0, 255));
	mExpBar.setPosition(sf::Vector2f(10.f, 45.f));

	mHealthText.setPosition(sf::Vector2f((10.f + size.x / 2.f), (10.f + size.y / 2.f)));
	mExpText.setPosition((10.f + size.x / 2.f), (45.f + size.y / 2.f));
}

void GameState::draw()
{
	mWorld[mCurrentArea.x][mCurrentArea.y]->draw();

	getContext().window->draw(mStatusText);
	
	

	// determining the readout
	sf::Vector2f size = mHealthBarBase.getSize();
	
	int current = mPlayerCreature.getHitpoints();
	int max = mPlayerCreature.getMaxHitpoints();
	float fraction = current / (max * 1.f);
	
	mHealthBar.setSize(sf::Vector2f((size.x * fraction), size.y));

	mHealthText.setString("HP: " + std::to_string(current) + " / " + std::to_string(max));
	centerOrigin(mHealthText);
	mHealthText.setPosition(sf::Vector2f((10.f + size.x / 2.f), (10.f + size.y / 2.f)));
	
	getContext().window->draw(mHealthBarBase);
	getContext().window->draw(mHealthBar);
	getContext().window->draw(mHealthText);

	current = mPlayerCreature.getExp();
	max = mPlayer.getLevelThreshold();
	fraction = current / (max * 1.f);

	mExpBar.setSize(sf::Vector2f((size.x * fraction), size.y));
	
	mExpText.setString("EXP: " + std::to_string(current) + " / " + std::to_string(max));
	centerOrigin(mExpText);
	mExpText.setPosition((10.f + size.x / 2.f), (45.f + size.y / 2.f));

	getContext().window->draw(mExpBarBase);
	getContext().window->draw(mExpBar);
	getContext().window->draw(mExpText);
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
	checkLevelConditions();

	mPlayer.handleRealtimeInput(mQueue);

	updateStatus();

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// Game input handling
	mPlayer.handleEvent(event, mQueue);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
		requestStackPush(States::Character);

	return true;
}

void GameState::initializeWorld(Context context)
{
	
	for (int x = 0; x < Areas.size(); x++)
	{
		mWorld.push_back(std::vector<Area*>());
		for (int y = 0; y < Areas[x].size(); y++)
		{
			mWorld[x].push_back(new Area(*context.window, *context.textures, &mQueue, Areas[x][y], &mPlayerCreature, &mEntityFactory));
			mRequiredKills += Areas[x][y].enemySpawns.size();
		}
	}

	sf::View view =  sf::View{context.window->getDefaultView()};

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

void GameState::updateStatus()
{
	std::string statusStr = "Press Space to attack. \n"; 
	statusStr += "Press F to use your bow. \n";
	statusStr += "Press C to see stats \n";

	if (getContext().player->getLevelStatus() == Player::UnallocatedPoints)
	{
		statusStr += "Level Up! Press C to allocate points";
	}
	mStatusText.setString(statusStr);

	
}

void GameState::checkLevelConditions()
{
	Player::LevelStatus status = getContext().player->getLevelStatus();
	int threshold = getContext().player->getLevelThreshold();

	if (status != Player::UnallocatedPoints)
	{
		if (mPlayerCreature.getExp() >= threshold)
		{
			mPlayerCreature.setExp(mPlayerCreature.getExp() - threshold);
			getContext().player->onLevelUp();
			mPlayerCreature.repair(1000);
		}
	}

	if (mPreviousLevelStatus != status)
	{
		mPlayerCreature.updateData(getContext().player->getPlayerStats());
	}
	mPreviousLevelStatus = status;
}