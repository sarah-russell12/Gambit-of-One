/*
Button.h

Date Last Updated: June 20, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use "facilities" header files anymore
*/

#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"
#include "ResourceHolder.hpp"
#include "UtilityFunctions.hpp"
#include <functional>

namespace GUI
{

	class Button : public Component
	{
	public:
		typedef std::shared_ptr<Button> Ptr;
		typedef std::function<void()> Callback;

		enum Type
		{
			Big,
			Small,
		};

	public:
		Button(const FontHolder& fonts, const TextureHolder& textures, Type type);

		virtual bool	isSelectable() const;
		virtual void	select();
		virtual void	deselect();

		virtual bool	isActive() const;
		virtual void	activate();
		virtual void	deactivate();

		virtual void	handleEvent(const sf::Event& event);

		void			setCallback(Callback callback);
		void			setText(const std::string& text);
		void			setToggle(bool flag);

	private:
		virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Sprite				mSprite;
		sf::Text				mText;
		bool					mIsToggle;
		const sf::Texture&		mNormalTexture;
		const sf::Texture&		mSelectedTexture;
		const sf::Texture&		mPressedTexture;
		Callback				mCallback;
		Type					mType;
	};
}

#endif //BUTTON_H