/*
UtilityFunctions.hpp

Date Last Updated: June 24, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use most of "facilities" header files anymore
- June 24, 2015:
	- Added two toString functions
	- Added UtilityFunctions.inl
- June 25, 2015:
	- Moved distance and collision to SceneNode files
*/

#ifndef UTILITY_FUNCTIONS_HPP
#define UTILITY_FUNCTIONS_HPP

#include "SFML_facilities.h"


#include <random>
#include <cmath>
#include <ctime>
#include <cassert>
#include <assert.h>
#include <sstream>

class SceneNode;
class Entity;

void			centerOrigin(sf::Text text);
void			centerOrigin(sf::Sprite sprite);

float			toDegree(float radian);
float			toRadian(float degree);

float			length(sf::Vector2f vector);

sf::Vector2f	unitVector(sf::Vector2f vector);

bool			collision(const SceneNode& lhs, const SceneNode& rhs);

namespace
{
	std::default_random_engine createRandomEngine();
	auto RandomEngine = createRandomEngine();
}

int randomInt(int bound);

template<typename T>
std::string		toString(const T& value);

std::string		toString(sf::Keyboard::Key key);

#include "UtilityFunctions.inl"

#endif //UTILITY_FUNCTIONS_HPP