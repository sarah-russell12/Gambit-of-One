#include "Headers/Application.h"

Application::Application() :
mWindow(sf::VideoMode(640, 480), "Gambit of One", sf::Style::Close),
mTextures(),
mFonts(),
mPlayer(),
mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
{
	mWindow.setKeyRepeatEnabled(false);

	loadResources();

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

void Application::loadResources()
{
	mFonts.load(Fonts::Main, "Media/Sansation.ttf");

	std::string path = "Media/Textures/";
	mTextures.load(Textures::HeroFront,			path + "HeroFront.png");
	mTextures.load(Textures::HeroAttack,		path + "HeroAttack.png");
	mTextures.load(Textures::HeroFire,			path + "HeroFire.png");
	mTextures.load(Textures::HeroFire,			path + "HeroFire.png");
	mTextures.load(Textures::Rat,				path + "Rat.png");
	mTextures.load(Textures::RatAttack,			path + "RatAttack.png");
	mTextures.load(Textures::Bandit,			path + "Bandit.png");
	mTextures.load(Textures::BanditAttack,		path + "BanditAttack.png");
	mTextures.load(Textures::Archer,			path + "Archer.png");
	mTextures.load(Textures::ArcherFire,		path + "ArcherFire.png");
	mTextures.load(Textures::HealthPotion,		path + "HealthPotion.png");
	mTextures.load(Textures::Quiver,			path + "Quiver.png");
	mTextures.load(Textures::WoodHouse,			path + "WoodHouse.png");
	mTextures.load(Textures::DirtRoad,			path + "DirtRoad.png");
	mTextures.load(Textures::TitleScreen,		path + "TitleScreen.png");
	mTextures.load(Textures::ButtonNormal,		path + "ButtonNormal.png");
	mTextures.load(Textures::ButtonSelected,	path + "ButtonSelected.png");
	mTextures.load(Textures::ButtonPressed,		path + "ButtonPressed.png");
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

	mWindow.display();
}