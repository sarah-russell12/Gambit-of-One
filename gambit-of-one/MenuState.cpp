#include "MenuState.h"

MenuState::MenuState(StateStack& stack, Context& context) :
State(stack, context),
//mOptions(),
//mOptionIndex(0),
mGUIContainer(),
mBackgroundSprite()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
	sf::Font& font = context.fonts->get(Fonts::Main);

	auto playButton = std::make_shared<GUI::Button>(*context.fonts, 
		*context.textures, GUI::Button::Big);
	playButton->setPosition(100, 300);
	playButton->setText("Play");
	playButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::Game);
	});
	mGUIContainer.pack(playButton);

	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts,
		*context.textures, GUI::Button::Big);
	settingsButton->setPosition(100, 350);
	settingsButton->setText("Key Bindings");
	settingsButton->setCallback([this]()
	{
		requestStackPush(States::Settings);
	});
	mGUIContainer.pack(settingsButton);

	auto exitButton = std::make_shared<GUI::Button>(*context.fonts, 
		*context.textures, GUI::Button::Big);
	exitButton->setPosition(100, 400);
	exitButton->setText("Exit");
	exitButton->setCallback([this]()
	{
		requestStackClear();
	});
	mGUIContainer.pack(exitButton);

}

bool MenuState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time)
{
	return true;
}