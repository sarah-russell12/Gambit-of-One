/*
Application.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/

#include "Application.hpp"
#include "Utility.hpp"
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "TitleState.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "SettingsState.hpp"
#include "GameOverState.hpp"



const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	: mWindow(sf::VideoMode(1024, 768), "Gambit of One", sf::Style::Close, sf::ContextSettings())
	, mTextures()
	, mFonts()
	, mPlayer()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);

	mFonts.load(Fonts::Main, "Media/Sansation.ttf");

	mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");
	mTextures.load(Textures::ButtonNormal, "Media/Textures/ButtonNormal.png");
	mTextures.load(Textures::ButtonSelected, "Media/Textures/ButtonSelected.png");
	mTextures.load(Textures::ButtonPressed, "Media/Textures/ButtonPressed.png");
	mTextures.load(Textures::Hero, "Media/Textures/HeroSpriteSheet.png");
	mTextures.load(Textures::Rat, "Media/Textures/RatSpriteSheet.png");
	mTextures.load(Textures::Bandit, "Media/Textures/BanditSpriteSheet.png");
	mTextures.load(Textures::Archer, "Media/Textures/ArcherSpriteSheet.png");
	mTextures.load(Textures::Arrow, "Media/Textures/Arrow.png");
	mTextures.load(Textures::HealthRefill, "Media/Textures/HealthPotion.png");
	mTextures.load(Textures::Rock, "Media/Textures/Rock.png");
	mTextures.load(Textures::BigTree1, "Media/Textures/BigTree.png");
	mTextures.load(Textures::SmallTree1, "Media/Textures/TinyTree.png");
	mTextures.load(Textures::TreeWallLong, "Media/Textures/TreeWallWhole.png");
	mTextures.load(Textures::TreeWallLeftCorner, "Media/Textures/TreeWallLeftCorner.png");
	mTextures.load(Textures::TreeWallRightCorner, "Media/Textures/TreeWallRightCorner.png");
	mTextures.load(Textures::Fence, "Media/Textures/Fence.png");
	mTextures.load(Textures::LeftEndDirtRoad, "Media/Textures/DirtRoadLeftEnd.png");
	mTextures.load(Textures::RightEndDirtRoad, "Media/Textures/DirtRoadRightEnd.png");

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10u);

	registerStates();
	mStateStack.pushState(States::Title);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			if (mStateStack.isEmpty())
				mWindow.close();
		}

		updateStatistics(dt);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<SettingsState>(States::Settings);
	mStateStack.registerState<GameOverState>(States::GameOver);
}