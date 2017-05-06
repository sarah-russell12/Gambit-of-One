/*
ClickButton.h

Date Created: December 13, 2016

This button is an interactive part of the GUI that can be clicked.  It can also
be any size or color scheme.  This was a long time coming.
*/

#ifndef CLICK_BUTTON_H
#define CLICK_BUTTON_H
#pragma once

#include "Component.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace GUI
{

	class ClickButton : public Component
	{
	public:
		typedef std::shared_ptr<ClickButton>		Ptr;
		typedef std::function<void()>				Callback;

	public:
		ClickButton(const FontHolder& fonts, sf::Window* ref);

		void					setCallback(Callback callback);
		void					setText(const std::string& text);
		void					setToggle(bool flag);

		// Normal, Pressed, and Selected colors refer to the border of the button and text within
		void					setNormalColor(const sf::Color& normal);
		void					setSelectedColor(const sf::Color& selected);
		void					setPressedColor(const sf::Color& pressed);
		void					setFillColor(const sf::Color& fill);
		void					setSize(float width, float height);
		virtual void					setSize(const sf::Vector2f& size);
		virtual void					setPosition(const sf::Vector2f& pos);

		virtual bool			isSelectable() const;
		virtual void			select();
		virtual void			deselect();

		virtual void			activate();
		virtual void			deactivate();

		virtual void			handleEvent(const sf::Event& event);

	private:
		virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		Callback				mCallback;
		bool					mIsToggle;

		sf::RectangleShape		mBox;
		sf::Text				mText;
		
		sf::Color				mNormalColor;
		sf::Color				mSelectedColor;
		sf::Color				mPressedColor;
		sf::Color				mFillColor;

		sf::Window*				mWindow;
	};

}

#endif //CLICK_BUTTON_H