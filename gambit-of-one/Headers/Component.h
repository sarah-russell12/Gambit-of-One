/*
Component.h

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


#ifndef COMPONENT_H
#define COMPONENT_H

#include "SFML_facilities.h"

#include <memory>

namespace GUI
{
	class Component : public sf::Drawable, public sf::Transformable,
		private sf::NonCopyable
	{
	public:
		typedef std::shared_ptr<Component> Ptr;

	public:
		Component();
		virtual			~Component();
		virtual bool	isSelectable() const = 0;
		bool			isSelected() const;
		virtual void	select();
		virtual void	deselect();
		virtual bool	isActive() const;
		virtual void	activate();
		virtual void	deactivate();
		virtual void	handleEvent(const sf::Event& event) = 0;

	private:
		bool			mIsSelected;
		bool			mIsActive;
	};
}

#endif //COMPONENT_H