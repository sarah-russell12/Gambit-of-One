#include "Headers/Pickup.h"
#include "Headers/Creature.hpp"

namespace
{
	const std::vector<PickupData> PickupTable = initializePickupData();
}

// public
Pickup::Pickup(Type type, const TextureHolder& textures)
	: Entity(1)
	, mType(type)
	, mSprite(textures.get(PickupTable[type].texture))
{
	centerOrigin(mSprite);
}

unsigned int Pickup::getCategory() const
{
	return Category::Pickup;
}

sf::FloatRect Pickup::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void Pickup::apply(Creature& player) const
{
	PickupTable[mType].action(player);
}

// private
void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}