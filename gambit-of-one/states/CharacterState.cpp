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

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

CharacterState::CharacterState(StateStack& stack, Context context)
	: State(stack, context)
	, mStatNames()
	, mStatValues()
	, mContainer()
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
	mContainer.pack(panel);
	auto panelSize = panel->getMeasurements();

	sf::FloatRect bounds = mInstructionText.getGlobalBounds();
	mInstructionText.setPosition((windowSize.x - bounds.width - 10.f), bounds.height + 10.f);

	centerOrigin(mHeader);
	mHeader.setPosition(sf::Vector2f((panelSize.width / 2.f), 30.f));

	buildStats();
}

void CharacterState::buildStats()
{
	// This will be enough of a mess that it should be its own method
	sf::Font& display = getContext().fonts->get(Fonts::Display);
	sf::Font& main = getContext().fonts->get(Fonts::Main);
	CreatureData data = getContext().player->getPlayerStats();

	std::vector<unsigned int> stats;
	std::vector <sf::String> statNames;
	stats.push_back(1);
	statNames.push_back("Level");
	stats.push_back(data.strength);
	statNames.push_back("Strength");
	stats.push_back(data.dexterity);
	statNames.push_back("Dexterity");
	stats.push_back(data.intelligence);
	statNames.push_back("Intelligence");
	stats.push_back(data.constitution);
	statNames.push_back("Constitution");
	stats.push_back(data.charisma);
	statNames.push_back("Charisma");

	float maxWidth = 0;  // A buffer for setting the position of the stats
	for (size_t i = 0; i < stats.size(); i++)
	{
		float y = 110.f + (80.f * i);
		sf::Text statName;
		statName.setFont(main);
		statName.setCharacterSize(24);
		statName.setString(statNames[i]);
		statName.setPosition(sf::Vector2f(20.f, y));
		mStatNames.push_back(statName);

		float stringWidth = statName.getPosition().x + statName.getGlobalBounds().width + 20.f;

		maxWidth = std::max(maxWidth, stringWidth);
	}

	for (size_t i = 0; i < stats.size(); i++)
	{
		float y = 100.f + (80.f * i);
		auto statRead = std::make_shared<GUI::InlaidTextbox>(*getContext().fonts);
		statRead->setString(std::to_string(stats[i]));
		statRead->setPosition(sf::Vector2f(maxWidth, y));
		mContainer.pack(statRead);
	}
}

void CharacterState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mContainer);
	window.draw(mInstructionText);
	for (size_t i = 0; i < mStatNames.size(); i++)
	{
		window.draw(mStatNames[i]);
	}
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
	
	return false;
}