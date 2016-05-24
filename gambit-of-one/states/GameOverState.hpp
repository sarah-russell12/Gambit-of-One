/*
GameOverState.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

The Game Over State displays the results of the level played in the Game
State.
*/

#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "State.hpp"
#include "..\gui\Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameOverState : public State
{
public:
	GameOverState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Text			mGameOverText;
	sf::Time			mElapsedTime;
};

#endif // GAMEOVERSTATE_HPP