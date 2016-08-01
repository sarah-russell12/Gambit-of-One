/*
ResourceIdentifiers.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

This file is a collection of enumerations and type definitions specific to
texture and font resources.
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
	enum ID
	{
		TitleScreen = 0,
		ButtonNormal = 1,
		ButtonSelected = 2,
		ButtonPressed = 3,
		Hero = 4,
		Rat = 5,
		Bandit = 6,
		Archer = 7,
		Arrow = 8,
		HealthRefill = 9,
		Rock = 10,
		BigTree1 = 11,
		SmallTree1 = 12,
		TreeWallLong = 13,
		TreeWallVert = 14,
		TreeWallLeftCorner = 15,
		TreeWallRightCorner = 16,
		Fence = 17,
		LeftEndDirtRoad = 18,
		RightEndDirtRoad = 19,
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
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

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;

#endif // RESOURCEIDENTIFIERS_HPP