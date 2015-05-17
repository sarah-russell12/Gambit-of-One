#include "Command.h"

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [=](SceneNode& node, sf::Time dt)
	{
		//Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		//Downcast node and invoke function on dt
		fn(static_cast<GameObject&>(node), dt);
	}
}