/*
CommandQueue.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/

#include "CommandQueue.hpp"
#include "nodes\SceneNode.hpp"

void CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}

Command CommandQueue::pop()
{
	Command command = mQueue.front();
	mQueue.pop();
	return command;
}

bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}