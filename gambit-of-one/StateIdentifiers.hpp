/*
StateIdentifiers.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

This file contains the enumeration of the IDs of states that the program uses
*/

#ifndef STATEIDENTIFIERS_HPP
#define STATEIDENTIFIERS_HPP


namespace States
{
	enum ID
	{
		None,
		Title,
		Menu,
		Game,
		//Loading,
		Pause,
		Settings,
		GameOver
	};
}

#endif // STATEIDENTIFIERS_HPP