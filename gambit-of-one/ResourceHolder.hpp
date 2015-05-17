#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP
#include "SFML_Facilities.h"
#include "Enumerations.hpp"


template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void			load(Identifier id, const std::string& filename);
	Resource&		get(Identifier id);
	const Resource&	get(Identifier id) const;
	template <typename Parameter>
	void			load(Identifier id, const std::string& filename,
		const Parameter& secondParam);

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};


typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif //RESOUCE_HOLDER_HPP