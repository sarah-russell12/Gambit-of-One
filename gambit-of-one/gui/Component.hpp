/*
Component.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Chapter 6 focuses on creating a proper Graphical User Interface, or GUI.  This
requires we create our own parts for building this interface using the
resources inside of SFML.  The basic part of a GUI is a GUI Component, and it
is the class we build our other GUI elements off of.
*/

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>


namespace sf
{
	class Event;
}

namespace GUI
{

	class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
	public:
		typedef std::shared_ptr<Component> Ptr;


	public:
		Component();
		virtual				~Component();

		virtual bool		isSelectable() const = 0;
		bool				isSelected() const;
		virtual void		select();
		virtual void		deselect();

		virtual bool		isActive() const;
		virtual void		activate();
		virtual void		deactivate();

		virtual void		handleEvent(const sf::Event& event) = 0;


	private:
		bool				mIsSelected;
		bool				mIsActive;
	};

}


#endif // COMPONENT_HPP