#include "PauseState.h"

PauseState::PauseState(StateStack& stack, Context& context) :
State(stack, context),
mPausedText(),
mGUIContainer()
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();

	mPausedText.setFont(font);
	mPausedText.setString("Paused");
	mPausedText.setCharacterSize(40);
	centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	auto continueButton = std::make_shared<GUI::Button>(*context.fonts, 
		*context.textures, GUI::Button::Big);
	continueButton->setPosition(100, 250);
	continueButton->setText("Continue");
	continueButton->setCallback([this]()
	{
		requestStackPop();
	});
	mGUIContainer.pack(continueButton);

	auto menuButton = std::make_shared<GUI::Button>(*context.fonts, 
		*context.textures, GUI::Button::Big);
	menuButton->setPosition(100, 350);
	menuButton->setText("Main Menu");
	menuButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::Menu);
	});
	mGUIContainer.pack(menuButton);

}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(window.getSize()));

	window.draw(mGUIContainer);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);

	return false;
}