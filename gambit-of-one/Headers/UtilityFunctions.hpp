/*
UtilityFunctions.hpp

Sarah Russell

Date Last Updated: July 27, 2015

A set of global functions that multiple classes make use of.

Updates:
- July 20, 2015: Declared centerOrigin() and consolidated toString.hpp to here
- July 24, 2015: Defined the overloaded toString method to apply to
				 sf::Keyboard::Key
- July 26, 2015: Declared and defined the toRadian(), toDegree(), unitVector(),
				 and length() methods (I really just copied them over from the
				 textbook code...)
- July 27, 2015: Copied over the random number generators from the book code
*/

#ifndef UTILITY_FUNCTIONS_HPP
#define UTILITY_FUNCTIONS_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <cassert>
#include <sstream>

#include "SceneNode.h"

void			centerOrigin(sf::Sprite& sprite);
void			centerOrigin(sf::Text& text);

//Consolidating from ToString.hpp
template <typename T>
std::string		toString(const T& value);

std::string		toString(sf::Keyboard::Key key);

float			toRadian(float degree);
float			toDegree(float radian);

sf::Vector2f	unitVector(sf::Vector2f vector);
float			length(sf::Vector2f vector);

int				randomInt(int exclusiveMax);

#include "UtilityFunctions.inl"

#endif //UTILITY_FUNCTIONS_HPP