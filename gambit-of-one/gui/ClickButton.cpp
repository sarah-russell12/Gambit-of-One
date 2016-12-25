/*
ClickButton.cpp

Date Created: December 13, 2016

Defines all methods declared in ClickButton.h
*/

#include "ClickButton.h"
#include "Utility.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
	
	ClickButton::ClickButton(const FontHolder& fonts, sf::Window* ref)
		: mCallback()
		, mIsToggle(false)
		, mText("", fonts.get(Fonts::Main), 20)
		, mNormalColor(sf::Color(255, 215, 50, 255))
		, mSelectedColor(sf::Color(190, 70, 0, 255))
		, mPressedColor(sf::Color(175, 100, 255, 255))
		, mFillColor(sf::Color(70, 70, 70, 255))
		, mBox()
		, mWindow(ref)
	{
		mBox.setFillColor(mFillColor);
		mBox.setOutlineColor(mNormalColor);
		mBox.setOutlineThickness(5.f);
		mBox.setSize(sf::Vector2f(100, 50));

		//mText.setColor(mNormalColor);

		centerOrigin(mBox);
		centerOrigin(mText);
	}

	void ClickButton::setCallback(ClickButton::Callback callback)
	{
		mCallback = std::move(callback);
	}

	void ClickButton::setText(const std::string& string)
	{
		// In case the box and text need to have their positions reset
		sf::Vector2f currentPos = mBox.getPosition();
		mText.setString(string);

		// In case the text exceeds the size of the box
		float width = std::max(mBox.getLocalBounds().width, mText.getLocalBounds().width + 10.f);
		float height = 30.f;
		mBox.setSize(sf::Vector2f(width, height));

		// Resetting the positions of the InlaidBox
		centerOrigin(mText);
		centerOrigin(mBox);
		setPosition(currentPos);
	}

	void ClickButton::setToggle(bool flag)
	{
		mIsToggle = flag;
	}

	void ClickButton::setNormalColor(const sf::Color& normal)
	{
		mNormalColor = normal;
	}

	void ClickButton::setSelectedColor(const sf::Color& selected)
	{
		mSelectedColor = selected;
	}

	void ClickButton::setPressedColor(const sf::Color& pressed)
	{
		mPressedColor = pressed;
	}

	void ClickButton::setFillColor(const sf::Color& fill)
	{
		mFillColor = fill;
		mBox.setFillColor(fill);
	}

	// Note: this can never be smaller than the text within the box
	void ClickButton::setSize(float width, float height)
	{
		float w = std::max(width, mText.getGlobalBounds().width + 10.f);
		float h = std::max(height, mText.getGlobalBounds().height);
		mBox.setSize(sf::Vector2f(w, h));
		centerOrigin(mBox);
		mText.setPosition(mBox.getPosition());
	}

	void ClickButton::setSize(const sf::Vector2f& size)
	{
		setSize(size.x, size.y);
	}

	void ClickButton::setPosition(const sf::Vector2f& pos)
	{
		mBox.setPosition(pos);
		mText.setPosition(pos);
	}

	bool ClickButton::isSelectable() const
	{
		return true;
	}

	void ClickButton::select()
	{
		Component::select();

		mBox.setOutlineColor(mSelectedColor);
		//mText.setColor(mSelectedColor);
	}

	void ClickButton::deselect()
	{
		Component::deselect();

		mBox.setOutlineColor(mNormalColor);
		//mText.setColor(mNormalColor);
	}

	void ClickButton::activate()
	{
		Component::activate();

		if (mIsToggle)
		{
			mBox.setOutlineColor(mPressedColor);
			//mText.setColor(mPressedColor);
		}

		if (mCallback)
		{
			mCallback();
		}

		if (!mIsToggle)
		{
			deactivate();
		}
	}

	void ClickButton::deactivate()
	{
		Component::deactivate();

		if (isSelected())
		{
			mBox.setOutlineColor(mSelectedColor);
			//mText.setColor(mSelectedColor);
		} 
		else
		{
			mBox.setOutlineColor(mNormalColor);
			//mText.setColor(mNormalColor);
		}
	}

	void ClickButton::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonReleased)
		{
			sf::Vector2i relpos = sf::Mouse::getPosition(*mWindow);
			sf::Vector2f pos{ (relpos.x * 1.f), (relpos.y * 1.f) };

			if (mBox.getGlobalBounds().contains(pos))
			{
				activate();
			}
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			sf::Vector2i relpos = sf::Mouse::getPosition(*mWindow);
			sf::Vector2f pos{ (relpos.x * 1.f), (relpos.y * 1.f) };

			if (mBox.getGlobalBounds().contains(pos))
			{
				select();
			}
			else if (Component::isSelected())
			{
				deselect();
			}
		}
	}

	void ClickButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mBox, states);
		target.draw(mText, states);
	}
}