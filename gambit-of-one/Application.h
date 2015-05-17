/*
	Application.h

	Date Last Updated: April 16, 2015

	This header file was made during the Spring 2015 SFML Game Development 
	Tutorial at New College of Florida.  This code follows the code from the
	textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius 
	Hansson, and Jan Haller.
*/

#ifndef APPLICATION_H
#define APPLICATION_H
#include "SFML_facilities.h"
#include "StateStack.hpp"
#include "Enumerations.hpp"
#include "States_Facilities.h"
#include "ResourceHolder.hpp"

class Application
{
public:
						Application();
	void				run();

private:
	void				registerStates();
	void				processInput();
	void				update(sf::Time dt);
	void				render();
	

private:
	static const sf::Time	TimePerFrame;
	StateStack				mStateStack;
	sf::RenderWindow		mWindow;
	TextureHolder			mTextures;
	FontHolder				mFonts;
	Player					mPlayer;

};

#endif //APPLICATION_H