/*
Container.h

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

#ifndef CONTAINER_H
#define CONTAINER_H

#include "Component.h"
#include "ResourceHolder.hpp"
#include <vector>

namespace GUI 
{
	class Container : public Component
	{
	public:
		typedef std::shared_ptr<Container> Ptr;

	public:
						Container();
		void			pack(Component::Ptr component);

		virtual bool	isSelectable() const;
		virtual void	handleEvent(const sf::Event& event);

	private:
		bool			hasSelection() const;
		void			select(std::size_t index);
		void			selectPrevious();
		void			selectNext();
		virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		std::vector<Component::Ptr> mChildren;
		int mSelectedChild;
	};
}

#endif //CONTAINER_H