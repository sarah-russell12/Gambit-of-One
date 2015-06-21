#ifndef UTILITY_FUNCTIONS_HPP
#define UTILITY_FUNCTIONS_HPP

#include "SFML_facilities.h"
#include "Entity.h"
#include "SceneNode.h"

#include <random>
#include <cmath>
#include <ctime>
#include <cassert>
#include <assert.h>
#include <sstream>

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

float			distance(Entity e1, Entity e2);

#endif //UTILITY_FUNCTIONS_HPP