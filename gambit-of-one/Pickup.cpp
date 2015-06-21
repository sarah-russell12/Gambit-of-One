#include "Headers/Pickup.h"

Pickup::Pickup(Type type, const TextureHolder& textures)
	: Entity(1)
	, mType(type)
	, mSprite(textures.get(PickupTable[type].texture))
{
	centerOrigin(mSprite);
}

void Pickup::apply(Aircraft& player) const
{
	PickupTable[mType].action(player);
}