#ifndef PICKUP_H
#define PICKUP_H

#include "Entity.h"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "SFML_facilities.h"
#include "UtilityFunctions.hpp"


namespace
{
	const std::vector<PickupData> PickupTable = initializePickupData();
}

class Pickup : public Entity
{
public:
	enum Type
	{
		HealthRefill,
		ArrowRefill,
		TypeCount,
	};

public:
	Pickup(Type type, const TextureHolder& textures);

	virtual unsigned int		getCategory() const;
	virtual sf::FloatRect		getBoundingRect() const;

	void						apply(Creature& player) const;

protected:
	virtual void		drawCurrent(sf::RenderTarget& target,
						sf::RenderStates states) const;

private:
	Type				mType;
	sf::Sprite			mSprite;
};

#endif //PICKUP_H