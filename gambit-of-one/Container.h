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