#include "Application.h"

Application::Application() :
mWindow(sf::VideoMode(640, 480), "Gambit of One", sf::Style::Close),
mTextures(),
mFonts(),
mPlayer(),
mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
{
	mWindow.setKeyRepeatEnabled(false);

	mFonts.load(Fonts::Main, "Media/Sansation.ttf");

	mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");
	mTextures.load(Textures::BigButtonNormal, "Media/Textures/BigButtonNormal.png");
	mTextures.load(Textures::BigButtonSelected, "Media/Textures/BigButtonSelected.png");
	mTextures.load(Textures::BigButtonPressed, "Media/Textures/BigButtonPressed.png");

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
			{
				mWindow.close();
			}
		}
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

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<SettingsState>(States::Settings);
	mStateStack.registerState<GameOverState>(States::GameOver);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());

	mWindow.display();
}