/*
Container.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

The Container is a manager of other GUI Components.  It may or may not be the
sole manager of a Component.  It will tell the Components under its management
which are active or selected, and which are not.
*/

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "Component.hpp"

#include <vector>
#include <memory>


namespace GUI
{

	class Container : public Component
	{
	public:
		typedef std::shared_ptr<Container> Ptr;


	public:
		Container();

		void				pack(Component::Ptr component);

		virtual bool		isSelectable() const;
		virtual void		handleEvent(const sf::Event& event);


	private:
		virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

		bool				hasSelection() const;
		void				select(std::size_t index);
		void				selectNext();
		void				selectPrevious();


	private:
		std::vector<Component::Ptr>		mChildren;
		int								mSelectedChild;
	};

}

#endif // CONTAINER_HPP