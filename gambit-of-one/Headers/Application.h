/*
Application.h

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

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Enumerations.hpp"
#include "GameState.h"
#include "GameOverState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "Player.h"
#include "ResourceHolder.hpp"
#include "SettingsState.h"
#include "SFML_facilities.h"
#include "State.h"
#include "StateStack.hpp"
#include "TitleState.h"
#include "UtilityFunctions.hpp"




class Application
{
public:
						Application();
	void				run();

private:
	void				loadResources();
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