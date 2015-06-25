#include "Headers/SettingsState.h"

SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
	, mGUIContainer()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
	
	addButtonLabel(Player::MoveLeft, 125.f, "Move Left", context);
	addButtonLabel(Player::MoveRight, 175.f, "Move Right", context);
	addButtonLabel(Player::MoveUp, 225.f, "Move Up", context);
	addButtonLabel(Player::MoveDown, 275.f, "Move Down", context);
	addButtonLabel(Player::MoveDown, 325.f, "Melee Attack", context);
	addButtonLabel(Player::MoveDown, 375.f, "Fire Arrow", context);

	updateLabels();

	auto backButton = std::make_shared<GUI::Button>(*context.fonts, 
		*context.textures, GUI::Button::Big);
	backButton->setPosition(400, 375);
	backButton->setText("Exit");
	backButton->setCallback([this]()
	{
		requestStackClear();
	});
	mGUIContainer.pack(backButton);
}

//So apparently the book code as a function that they DON'T mention in the book 
//does all the repetative stuff for you.  Why didn't I think of that?
void SettingsState::addButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
	mBindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, 
		*context.textures, GUI::Button::Big);
	mBindingButtons[action]->setPosition(80.f, y);
	mBindingButtons[action]->setText(text);
	mBindingButtons[action]->setToggle(true);

	mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	mBindingLabels[action]->setPosition(300.f, y + 15.f);

	mGUIContainer.pack(mBindingButtons[action]);
	mGUIContainer.pack(mBindingLabels[action]);
}

void SettingsState::updateLabels()
{
	Player& player = *getContext().player;
	for (std::size_t i = 0; i < Player::ActionCount; ++i)
	{
		sf::Keyboard::Key key =
			player.getAssignedKey(static_cast<Player::Action>(i));
		mBindingLabels[i]->setText(toString(key));
	}
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;
	for (std::size_t action = 0; action < Player::ActionCount; ++action)
	{
		if (mBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				getContext().player->assignKey(
					static_cast<Player::Action>(action), event.key.code);
				mBindingButtons[action]->deactivate();
			}
			break;
		}
	}

	if (isKeyBinding)
	{
		updateLabels();
	}
	else
	{
		mGUIContainer.handleEvent(event);
	}
	return false;
}

bool SettingsState::update(sf::Time dt)
{
	return true;
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}