/*
Utility.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

This file contains a collection of global functions that are used in different
parts of the program often.
*/

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <sstream>


namespace sf
{
	class Sprite;
	class Text;
}

template <typename T>
std::string		toString(const T& value);

std::string		toString(sf::Keyboard::Key key);

void			centerOrigin(sf::Sprite& sprite);
void			centerOrigin(sf::Text& text);

float			toDegree(float radian);
float			toRadian(float degree);

int				randomInt(int exclusiveMax);

float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);


#include "Utility.inl"
#endif // BOOK_UTILITY_HPP