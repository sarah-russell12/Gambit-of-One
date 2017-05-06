/*
CharacterState.cpp

Date Created: October 27, 2016

Defines all the methods declared in CharacterState.h
*/

#include "CharacterState.h"
#include "Utility.hpp"
#include "ResourceIdentifiers.hpp"
#include "DataTables.hpp"
#include "Player.hpp"
#include "Panel.h"
#include "ClickButton.h"
#include "Label.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

using namespace std::placeholders;

CharacterState::CharacterState(StateStack& stack, Context context)
	: State(stack, context)
	, mLvlReadouts()
	, mStatsReadouts()
	, mStatsContainer()
	, mLvlContainer(true)
	, mInstructionText("Press Esc or C to return", context.fonts->get(Fonts::Main), 18)
	, mHeader("Stats", context.fonts->get(Fonts::Display), 40)
{
	buildScreen();
}

void CharacterState::buildScreen()
{
	sf::Font& main = getContext().fonts->get(Fonts::Main);
	CreatureData data = getContext().player->getPlayerStats();

	sf::Vector2f windowSize(getContext().window->getSize());

	auto panel = std::make_shared<GUI::Panel>(windowSize);
	mStatsContainer.pack(panel);
	auto panelSize = panel->getMeasurements();

	sf::FloatRect bounds = mInstructionText.getGlobalBounds();
	mInstructionText.setPosition((windowSize.x - bounds.width - 10.f), bounds.height + 10.f);

	centerOrigin(mHeader);
	mHeader.setPosition(sf::Vector2f((panelSize.width / 2.f), 30.f));

	buildStats();

	if (getContext().player->getLevelStatus() == Player::UnallocatedPoints)
	{
		buildLevelStats();
	}
}

void CharacterState::buildStats()
{
	// This will be enough of a mess that it should be its own method

	std::vector <sf::String> statNames;
	statNames.push_back("Level");
	statNames.push_back("Strength");
	statNames.push_back("Dexterity");
	statNames.push_back("Intelligence");
	statNames.push_back("Constitution");
	statNames.push_back("Charisma");

	float maxWidth = 0;  // A buffer for setting the position of the stats
	for (size_t i = 0; i < statNames.size(); i++)
	{
		float y = 110.f + (80.f * i);
		auto label =  std::make_shared<GUI::Label>(statNames[i], *getContext().fonts);
		label->setPosition(sf::Vector2f(20.f, y));
		mStatsContainer.pack(label);
	}

	for (size_t i = 0; i < 6; i++)
	{
		float y = 100.f + (80.f * i);
		auto statRead = std::make_shared<GUI::InlaidTextbox>(*getContext().fonts);
		statRead->setPosition(sf::Vector2f(140.f, y));
		mStatsContainer.pack(statRead);
		mStatsReadouts.push_back(statRead);
	}

	CreatureData stats = getContext().player->getPlayerStats();
	mStatsReadouts[0]->setString(std::to_string(stats.level));
	mStatsReadouts[1]->setString(std::to_string(stats.strength));
	mStatsReadouts[2]->setString(std::to_string(stats.dexterity));
	mStatsReadouts[3]->setString(std::to_string(stats.intelligence));
	mStatsReadouts[4]->setString(std::to_string(stats.constitution));
	mStatsReadouts[5]->setString(std::to_string(stats.charisma));
}

void CharacterState::buildLevelStats()
{
	CreatureData data = getContext().player->getPlayerStats();
	int stats[5];

	stats[0] = data.strength;
	stats[1] = data.dexterity;
	stats[2] = data.intelligence;
	stats[3] = data.constitution;
	stats[4] = data.charisma;

	mPointPool = getContext().player->getPoints();
	for (size_t i = 0; i < 5; i++)
	{
		float y = 100.f + (80.f * (i + 1));

		auto addButton = std::make_shared<GUI::ClickButton>(*getContext().fonts, getContext().window);
		addButton->setSize(30.f, 30.f);
		addButton->setText("+");
		addButton->setPosition(sf::Vector2f(235.f, y + 15.f));

		addButton->setCallback([this, i]() { incrementStat(i); });

		auto subButton = std::make_shared<GUI::ClickButton>(*getContext().fonts, getContext().window);
		subButton->setSize(30.f, 30.f);
		subButton->setText("-");
		subButton->setPosition(sf::Vector2f(290.f, y + 15.f));

		subButton->setCallback([this, i]() { decrementStat(i); });

		auto lvlStatRead = std::make_shared<GUI::InlaidTextbox>(*getContext().fonts);
		lvlStatRead->setString(std::to_string(stats[i]));
		lvlStatRead->setPosition(sf::Vector2f(330.f, y));
		mLvlValues[i] = stats[i];
		mLvlBases[i] = stats[i];
		mLvlReadouts.push_back(lvlStatRead);

		mLvlContainer.pack(addButton);
		mLvlContainer.pack(subButton);
		mLvlContainer.pack(lvlStatRead);
	}

	auto pointsLabel = std::make_shared<GUI::Label>("Points Available", *getContext().fonts);
	pointsLabel->setPosition(20.f, 615.f);
	mLvlContainer.pack(pointsLabel);

	auto pointsBox = std::make_shared<GUI::InlaidTextbox>(*getContext().fonts);
	pointsBox->setPosition(sf::Vector2f(140.f, 605.f));
	pointsBox->setString(std::to_string(mPointPool));
	mLvlReadouts.push_back(pointsBox);
	mLvlContainer.pack(pointsBox);

	auto allocateButton = std::make_shared<GUI::ClickButton>(*getContext().fonts, getContext().window);
	allocateButton->setText("Allocate Points");
	allocateButton->setCallback([this]() { assignPoints(); });
	allocateButton->setPosition(sf::Vector2f(300.f, 605.f));
	mLvlContainer.pack(allocateButton);
}

void CharacterState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mStatsContainer);
	if (getContext().player->getLevelStatus() == Player::UnallocatedPoints)
	{
		window.draw(mLvlContainer);
	}
	window.draw(mInstructionText);
	window.draw(mHeader);
}

bool CharacterState::update(sf::Time dt)
{
	return false;
}

bool CharacterState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::C))
		requestStackPop();
	else
		if (getContext().player->getLevelStatus() == Player::UnallocatedPoints)
		{
			mLvlContainer.handleEvent(event);
		}
	
	return false;
}

void CharacterState::incrementStat(int index)
{
	if (mPointPool > 0)
	{
		mPointPool -= 1;
		mLvlValues[index] += 1;
		mLvlReadouts[index]->setString(std::to_string(mLvlValues[index]));
		mLvlReadouts[5]->setString(std::to_string(mPointPool));
	}
}

void CharacterState::decrementStat(int index)
{
	if (mLvlValues[index] > mLvlBases[index])
	{
		mPointPool += 1;
		mLvlValues[index] -= 1;
		mLvlReadouts[index]->setString(std::to_string(mLvlValues[index]));
		mLvlReadouts[5]->setString(std::to_string(mPointPool));
	}
}

void CharacterState::assignPoints()
{
	getContext().player->setPlayerStats(mLvlValues, mPointPool);

	CreatureData stats = getContext().player->getPlayerStats();
	mStatsReadouts[0]->setString(std::to_string(stats.level));
	mStatsReadouts[1]->setString(std::to_string(stats.strength));
	mStatsReadouts[2]->setString(std::to_string(stats.dexterity));
	mStatsReadouts[3]->setString(std::to_string(stats.intelligence));
	mStatsReadouts[4]->setString(std::to_string(stats.constitution));
	mStatsReadouts[5]->setString(std::to_string(stats.charisma));
	
	for (int i = 0; i < 5; i++)
	{
		mLvlBases[i] = mLvlValues[i];
	}
}