#ifndef CENTERING_H
#define CENTERING_H

/*
  The new equivalent to the Book's Utility.hpp
*/

#include "SFML_facilities.h"
#include "Entity.h"
#include <assert.h>

void centerOrigin(sf::Text text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void centerOrigin(sf::Sprite sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

float toDegree(float radian)
{
	return 180.f / 3.141592653589793238462643383f * radian;
}

float toRadian(float degree)
{
	return 3.141592653589793238462643383f / 180.f * degree;
}

float length(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f unitVector(sf::Vector2f vector)
{
	assert(vector != sf::Vector2f(0.f, 0.f));
	return vector / length(vector);
}

float distance(Entity e1, Entity e2)
{
	float e1x = e1.getPosition().x;
	float e1y = e1.getPosition().y;
	float e2x = e2.getPosition().x;
	float e2y = e2.getPosition().y;

	return std::sqrt((e1x + e2x) * (e1x + e2x) + (e1y + e2y) * (e1y + e2y));
}

bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

#endif //CENTERING_H