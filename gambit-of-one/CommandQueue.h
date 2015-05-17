/*
	CommandQueue.h

	Date Last Updated: April 16, 2015

	This header file was made during the Spring 2015 SFML Game Development
	Tutorial at New College of Florida.  This code follows the code from the
	textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
	Hansson, and Jan Haller.
*/


#ifndef COMMAND_QUEUE_H
#define	COMMAND_QUEUE_H	
#include "Command.h"
#include <queue>

class CommandQueue
{
public:
	void		push(const Command& command);
	Command		pop();
	bool		isEmpty() const;

private:
	std::queue<Command> mQueue;
};

#endif //COMMAND_QUEUE_H