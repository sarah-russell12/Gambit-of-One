/*
Label.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

The Label is a GUI Component that conveys text information to the user. It is
not selectable, so it doesn't do anything special outside of that.
*/

#ifndef LABEL_HPP
#define LABEL_HPP

#include "Component.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/Text.hpp>


namespace GUI
{

	class Label : public Component
	{
	public:
		typedef std::shared_ptr<Label> Ptr;


	public:
		Label(const std::string& text, const FontHolder& fonts);

		virtual bool		isSelectable() const;
		void				setText(const std::string& text);

		virtual void		handleEvent(const sf::Event& event);


	private:
		virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		sf::Text			mText;
	};

}

#endif // LABEL_HPP