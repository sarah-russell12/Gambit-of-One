/*
Scenery.cpp

Date Last Updated: March 5, 2015
*/

#include "Scenery.h"

#include "..\Category.hpp"
#include "..\DataTables.hpp"
#include "..\Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

std::vector<SceneryData> Table = initializeSceneryData();

Scenery::Scenery(Type type, const TextureHolder& textures)
	: Entity(1)
	, mType(type)
	, mSprite(textures.get(Table[type].texture))
{
	centerOrigin(mSprite);
}


Scenery::~Scenery()
{
}

unsigned int Scenery::getCategory() const
{
	return Category::InertScenery;
}

sf::FloatRect Scenery::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

Scenery::Type Scenery::getType() const
{
	return mType;
}

void Scenery::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}