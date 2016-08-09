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
		TitleScreen,
		ButtonNormal,
		ButtonSelected,
		ButtonPressed,
		Hero,
		Rat,
		Bandit,
		Archer,
		Arrow,
		HealthRefill,
		Rock,
		BigTree1,
		SmallTree1,
		TreeWallHoriz,
		TreeWallVert,
		TreeWallLeftCorner,
		TreeWallRightCorner,
		Fence,
		DirtRoadEndW,
		DirtRoadEndE,
		DirtRoadEndN,
		DirtRoadEndS,
		DirtRoadHoriz,
		DirtRoadVert,
		DirtRoadCross,
		DirtRoadForkW,
		DirtRoadForkE,
		DirtRoadForkN,
		DirtRoadForkS,
		DirtRoadCornerNW,
		DirtRoadCornerNE,
		DirtRoadCornerSW,
		DirtRoadCornerSE,
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