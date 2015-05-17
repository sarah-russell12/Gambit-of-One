#include "Game.h"
#include "World.h"

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "SFML Application", sf::Style::Close, sf::ContextSettings())
{
	mWorld = World(mWindow);
	mTexture = sf::Texture();
	//mPlayer = sf::Sprite();
	if (!mTexture.loadFromFile("Media/Textures/Eagle.png")) {
		throw std::exception("Cannot load file.");
	}
	//mPlayer.setTexture(mTexture);
}

//Now will run at 60 fps
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();

		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			if (!mIsPaused)
			{
				update(TimePerFrame);
			}
		}
		render();
	}
}

void Game::processEvents() {

	sf::Event event;
	while (mWindow.pollEvent(event))
	{

		switch (event.type)
		{
		case sf::Event::GainedFocus:
			mIsPaused = false;
			break;
		case sf::Event::LostFocus:
			mIsPaused = true;
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}


void Game::update(sf::Time deltaTime)
{
	//mPlayer.move(movement * deltaTime.asSeconds());
	mWorld.update(deltaTime);
}

/* During each loop of the game, the render function clears the screen and
* replaces all the relevant items on the screen in the orientation they
* need to be in.
*/
void Game::render()
{
	mWindow.clear();
	mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.display();
}

void Game::processInput()
{
	CommandQueue& commands = mWorld.getCommandQueue();

	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mPlayer.handleEvent(event, commands);

		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}

		mPlayer.handleRealtimeInput(commands);
	}
}