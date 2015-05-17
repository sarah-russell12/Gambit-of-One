#include "Container.h"

GUI::Container::Container()
	: mChildren(), mSelectedChild(-1) {}

void GUI::Container::pack(Component::Ptr component)
{
	mChildren.push_back(component);
	if (!hasSelection() && component->isSelectable())
	{
		select(mChildren.size() - 1);
	}
}

bool GUI::Container::isSelectable() const
{
	return false;
}

void GUI::Container::handleEvent(const sf::Event& event)
{
	if (hasSelection() && mChildren[mSelectedChild]->isActive())
	{
		mChildren[mSelectedChild]->handleEvent(event);
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W
			|| event.key.code == sf::Keyboard::Up)
		{
			selectPrevious();
		}
		else if (event.key.code == sf::Keyboard::S
			|| event.key.code == sf::Keyboard::Down)
		{
			selectNext();
		}
		else if (event.key.code == sf::Keyboard::Return
			|| event.key.code == sf::Keyboard::Space)
		{
			if (hasSelection())
			{
				mChildren[mSelectedChild]->activate();
			}
		}
	}
}

void GUI::Container::select(std::size_t index)
{
	if (mChildren[index]->isSelectable())
	{
		if (hasSelection())
		{
			mChildren[mSelectedChild]->deselect();
		}
		mChildren[index]->select();
		mSelectedChild = index;
	}
}

void GUI::Container::selectNext()
{
	if (!hasSelection()) return;
	//Search next component that is selectable
	int next = mSelectedChild;
	do
		next = (next + 1) % mChildren.size();
	while (!mChildren[next]->isSelectable());
	//select that component
	select(next);
}

void GUI::Container::selectPrevious()
{
	if (!hasSelection()) return;
	//Search next component that is selectable
	int prev = mSelectedChild;
	do
		prev = (prev + mChildren.size() - 1) % mChildren.size();
	while (!mChildren[prev]->isSelectable());
	//select that component
	select(prev);
}

bool GUI::Container::hasSelection() const
{
	if (mSelectedChild == -1) return false;
	return true;
}

void GUI::Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (const Component::Ptr& component : mChildren)
	{
		target.draw(*component, states);
	}
}