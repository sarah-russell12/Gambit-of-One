/*
ResourceIdentifiers.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

This file is a collection of enumerations and type definitions specific to
texture and font resources.

Updates:
	September 28, 2016: Phasing out the Resource ID enums so that the
*/

#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	// Certain textures need to be referenced in this way
	enum ID
	{
		HealthRefill = 0,
		TitleScreen = 1,
		ButtonNormal = 2,
		ButtonSelected = 3,
		ButtonPressed = 4,
	};
}

namespace Fonts
{
	enum ID
	{
		Display = 0,		// A Display-type font, use for headers
		Main = 1,			// A non-Display-type font
	};
}

enum Compass
{
	South,
	East,
	North,
	West,
};

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, unsigned int>	TextureHolder;
typedef ResourceHolder<sf::Font, unsigned int>			FontHolder;

#endif // RESOURCEIDENTIFIERS_HPP