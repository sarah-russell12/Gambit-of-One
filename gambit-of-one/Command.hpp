/*
	Application.h

	Date Last Updated: April 16, 2015

	This header file was made during the Spring 2015 SFML Game Development
	Tutorial at New College of Florida.  This code follows the code from the
	textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
	Hansson, and Jan Haller.
*/

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "SFML_facilities.h"
#include "Enumerations.hpp"

#include <functional>


class SceneNode;

struct Command
{
	typedef std::function<void(SceneNode&, sf::Time)> Action;

	Command();
	std::function<void(SceneNode&, sf::Time)>	action;
	unsigned int								category;
};

template <typename GameObject, typename Function>
Command::Action derivedAction(Function fn)
{
	return [=](SceneNode& node, sf::Time dt)
	{
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}

Command::Command()
	: action()
	, category(Category::None) {}

#endif //COMMAND_HPP