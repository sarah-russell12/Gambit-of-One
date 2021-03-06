/*
Application.hpp

Date Last Updated: August 4, 2016

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

The application has control of a StateStack that handles the States of the
game, and handles the game loop in terms of conducting its parts to do thier
functions independent of each other in the right order.

This class uses the pugixml library (http://pugixml.org) to parse xml documents.
pugixml is Copyright (C) 2006-2015 Arseny Kapoulkine.

Updates:
	- August 4, 2016: Added loadResouces method once again, and added pugixml parsing
					  capabilities to it
*/

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Player.hpp"
#include "StateStack.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Application
{
public:
	Application();
	void					run();


private:
	void					processInput();
	void					update(sf::Time dt);
	void					render();

	void					updateStatistics(sf::Time dt);
	void					registerStates();

	void					loadResources();

private:
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	TextureHolder			mTextures;
	FontHolder				mFonts;
	Player					mPlayer;

	StateStack				mStateStack;

	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	std::size_t				mStatisticsNumFrames;
};

#endif // APPLICATION_HPP