#ifndef HUMANOID_H
#define HUMANOID_H

#include "SFML_facilities.h"
#include "Entity.h"
#include "ResourceHolder.hpp"

class Humanoid : public Entity
{
public:
	enum Type
	{
		Human,
		Elf,
	};

	explicit		Humanoid(Type type, const TextureHolder& textures);
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif //HUMANOID_H