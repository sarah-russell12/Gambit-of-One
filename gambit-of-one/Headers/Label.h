/*
Label.h

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

#ifndef LABEL_H
#define LABEL_H

#include "Component.h"
#include "ResourceHolder.hpp"

namespace GUI
{
	class Label : public Component
	{
	public:
		typedef std::shared_ptr<Label> Ptr;

	public:
						Label(const std::string& text, const FontHolder& fonts);

		virtual bool	isSelectable() const;
		virtual void	handleEvent(const sf::Event& event);
		void			setText(const std::string& text);

	private:
		void			draw(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		sf::Text mText;
	};
}

#endif //LABEL_H