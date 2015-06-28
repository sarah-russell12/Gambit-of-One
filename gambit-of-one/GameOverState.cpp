#include "Headers/GameOverState.h"

GameOverState::GameOverState(StateStack& stack, Context context)
	: State(stack, context)
	, mGameOverText()
	, mGUIContainer()
	, mBackgroundSprite()
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	mBackgroundSprite.setTexture(texture);

	auto menuButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	menuButton->setPosition(100, 300);
	menuButton->setText("Main Menu");
	menuButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::Menu);
	});
	mGUIContainer.pack(menuButton);

	auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	exitButton->setPosition(100, 350);
	exitButton->setText("Exit");
	exitButton->setCallback([this]()
	{
		requestStackPop();
	});
	mGUIContainer.pack(exitButton);

	sf::Font& font = context.fonts->get(Fonts::Main);
	mGameOverText.setFont(font);

	sf::Vector2f windowSize(context.window->getSize());
	if (context.player->getStatus() == Player::Failure)
		mGameOverText.setString("You Lose!");
	else
		mGameOverText.setString("You Win!");

	mGameOverText.setCharacterSize(50);
	centerOrigin(mGameOverText);
	mGameOverText.setPosition(100, 225);
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGameOverText);
	window.draw(mGUIContainer);
}

bool GameOverState::update(sf::Time)
{
	return true;
}

bool GameOverState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}