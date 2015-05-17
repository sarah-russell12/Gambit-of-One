#ifndef GUI_H
#define GUI_H

#include <vector>



	class Container : public Component
	{
	public:
		Container();
		void pack(Component::Ptr component);

	private:
		std::vector<Component::Ptr> mChildren;
		int mSelectedChild;
	};

	class Button : public Component
	{};

	class Label : public Component
	{};
}

#endif //GUI_H