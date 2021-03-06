/*
GameState.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

As was said in "State.hpp", the gameplay is a state of its own. And the original
running of the game loop is no longer necessary for game, so now the game's
function is to render a World and tell that World to change according to events and
changes in time that are passed down from the Application to the StateStack to
the Game.  For that to work we need to make a GameState that fits into the
StateStack structure.
*/

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"
#include "Area.h"
#include "Player.hpp"
#include "EntityFactory.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
	void				initializeWorld(Context context);
	void				changeArea();
	void				updateStatus();
	void				checkLevelConditions();

private:
	std::vector<std::vector<Area*>>				mWorld;
	sf::Vector2i								mCurrentArea;
	Player&										mPlayer;
	Creature									mPlayerCreature;
	int											mRequiredKills;
	sf::FloatRect								mAreaBounds;
	CommandQueue								mQueue;

	sf::Text									mStatusText;
	EntityFactory								mEntityFactory;
	Player::LevelStatus							mPreviousLevelStatus;

	// Bases for the heath and experience bars
	sf::RectangleShape							mHealthBarBase;
	sf::RectangleShape							mExpBarBase;

	// What actually changes
	sf::RectangleShape							mHealthBar;
	sf::RectangleShape							mExpBar;

	sf::Text									mHealthText;
	sf::Text									mExpText;
};

#endif // GAMESTATE_HPP