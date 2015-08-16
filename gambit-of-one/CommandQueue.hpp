/*
CommandQueue.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

A CommandQueue is the game's way of setting up Commands for itself.  It will
enqueue new Commands and dequeue Commands and make the SceneGraph react to
them.
*/

#ifndef COMMANDQUEUE_HPP
#define COMMANDQUEUE_HPP

#include "Command.hpp"

#include <queue>


class CommandQueue
{
public:
	void push(const Command& command);
	Command	pop();
	bool isEmpty() const;


private:
	std::queue<Command>	mQueue;
};

#endif // COMMANDQUEUE_HPP